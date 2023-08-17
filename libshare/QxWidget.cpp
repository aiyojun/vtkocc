#include "imp.h"
#include "QxWidget.h"

#include <utility>


int calc(QWidget* p, const std::string& str, bool isWidth=true) {
    std::string xStr = std::regex_replace(str, std::regex(" "), "");
    double r;
    if (QtTools::match(xStr, std::regex("^[0-9]+px$"))) {
        r = std::stoi(xStr.substr(0, xStr.length() - 2));
    } else if (QtTools::match(xStr, std::regex("^[0-9]+%$"))) {
        r = (isWidth ? p->width() : p->height()) * std::stod(xStr.substr(0, xStr.length() - 1)) * 0.01;
    } else if (QtTools::match(xStr, std::regex("^calc\\([0-9]+%([+-][0-9]+px)*\\)$"))) {
        size_t pos0 = xStr.find('%');
        r = (isWidth ? p->width() : p->height()) * std::stoi(xStr.substr(5, pos0 - 5)) * 0.01 ;
        std::string rest = xStr.substr(pos0 + 1, xStr.length() - pos0 - 2);
        while (rest.length() > 0) {
            size_t pos = rest.find("px");
            if (pos == std::string::npos)
                break;
            r += std::stoi(rest.substr(0, pos));
            rest = rest.substr(pos + 2);
        }
    } else
        throw std::runtime_error("error distance unit : " + xStr);
//    LOG("unit convert " + str + " => " + std::to_string((int)r));
    return (int) r;
}

QxWidget::QxWidget(QWidget *parent): QWidget(parent), type("QxWidget") {
    setAttribute(Qt::WA_StyledBackground, true);
}

QxWidget::QxWidget(std::string type, QWidget *parent): QWidget(parent), type(std::move(type)) {
    setAttribute(Qt::WA_StyledBackground, true);
}

QxWidget::~QxWidget() {
    for (auto & ptr : r_ptr) {
        delete ptr;
        ptr = nullptr;
    }
}

std::map<std::string, WidgetHandle> QxWidget::handles {
    {"widget",      QxBaseWidget::build},
    {"dock-button", QxDockButton::build},
};

QxWidget* QxWidget::uiParse(WidgetContext& context) {
    auto& root = context._template;
    if (!root.contains("type"))
        throw std::runtime_error("widget lack of type");
    if (!root.contains("name"))
        throw std::runtime_error("widget lack of name");
    auto name = root["name"].get<std::string>();
    auto type = root["type"].get<std::string>();

    if (handles.find(type) == handles.end())
        throw std::runtime_error("No such widget " + type);
    if (context._pool.find(name) != context._pool.end())
        throw std::runtime_error("Repeat widget " + name);

    auto& hd = handles[type];
    auto* r_ptr = hd(context);
    context._pool[name] = r_ptr;

    if (!root.contains("children"))
        return r_ptr;

    if (!root.contains("direction"))
        throw std::runtime_error("lack of direction");
    auto direction = root["direction"].get<std::string>();
//    auto* flex = r_ptr->buildFlex(direction == "vertical" ? QBoxLayout::Direction::TopToBottom : QBoxLayout::Direction::LeftToRight);

    int bx = context._begin.x(); int by = context._begin.y();

    for (auto& child_template : root["children"]) {
        WidgetContext child_context(child_template, r_ptr, context._pool, QPoint(bx, by));
        auto* child_ptr = uiParse(child_context);
        r_ptr->children.emplace_back(child_ptr);
//        flex->addWidget(child_ptr);
        if (direction == "vertical") {
            by += child_ptr->height();
        } else {
            bx += child_ptr->width();
        }
    }

    return r_ptr;
}

QWidget *QxWidget::parse(json& root, QWidget* parent, std::map<std::string, QWidget *>& pool) {
    WidgetContext context(root, parent, pool, QPoint(0, 0));
    auto* r = uiParse(context);
    r->setGeometry(0, 0,
        calc(parent, root["width"].get<std::string>()),
        calc(parent, root["height"].get<std::string>(), false));
    return r;
}

QxBaseWidget *QxBaseWidget::build(WidgetContext &context) {
    auto* p = new QxBaseWidget(context._parent);
    p->setTemplate(context._template);
    auto& root = context._template;
    p->setObjectName(QString(root["name"].get<std::string>().c_str()));
    p->setQxWidgetGeometryByTemplate();
//    LOG(p->objectName().toStdString()
//        + " width "  + std::to_string(calc(context._parent, root["width"].get<std::string>()))
//        + " height " + std::to_string(calc(context._parent, root["height"].get<std::string>(), false)));
    if (root.contains("qss"))
        p->setStyleSheet(QString("#").append(root["name"].get<std::string>().c_str()).append("{").append(root["qss"].get<std::string>().c_str()).append("}"));
    return p;
}

QxDockButton *QxDockButton::build(WidgetContext &context) {
    auto* p = new QxDockButton(context._parent);
    p->setTemplate(context._template);
    auto& root = context._template;

    if (!root.contains("text"))
        throw std::runtime_error("DockButton lack of text");
    if (!root.contains("icon"))
        throw std::runtime_error("DockButton lack of icon");
    if (!root.contains("button-direction"))
        throw std::runtime_error("DockButton lack of button-direction");

    p->setObjectName(QString(root["name"].get<std::string>().c_str()));
    if (root.contains("qss"))
        p->setStyleSheet(QString("#").append(root["name"].get<std::string>().c_str()).append("{").append(root["qss"].get<std::string>().c_str()).append("}"));

    auto width  = calc(context._parent, root["width" ].get<std::string>());
    auto height = calc(context._parent, root["height"].get<std::string>(), false);
    p->setFixedSize(width, height);
    auto direction = root["button-direction"].get<std::string>();
    auto* flex = p->buildFlex(direction == "vertical" ? QBoxLayout::Direction::TopToBottom : QBoxLayout::Direction::LeftToRight);
    auto* ptr_label = p->buildLabel(root["text"].get<std::string>().c_str());
    auto* ptr_image = p->buildLabel();
    auto icon_size = root["icon-size"].get<int>();
    auto space = root["space"].get<int>();
    ptr_image->setFixedSize(icon_size, icon_size);
    QtTools::setBackgroundImage(ptr_image, root["icon"].get<std::string>().c_str());
    flex->addWidget(ptr_image);
    flex->addWidget(ptr_label);
    flex->setSpacing(space);
    flex->setAlignment(Qt::AlignmentFlag::AlignCenter);
    flex->setGeometry(QRect(0, 0, width, height));
    return p;
}

void QxDockButton::mousePressEvent(QMouseEvent *event) {
    emit clicked();
}

void QxDockButton::mouseReleaseEvent(QMouseEvent *event) {

}

QBoxLayout* QxWidget::buildFlex(QBoxLayout::Direction direction) {
    auto* flex = new QBoxLayout(direction, this);
    flex->setSpacing(0); flex->setMargin(0);
//    if (QBoxLayout::Direction::TopToBottom == direction || QBoxLayout::Direction::BottomToTop == direction) {
//        flex->setAlignment(Qt::AlignmentFlag::AlignHCenter);
//    } else if (QBoxLayout::Direction::RightToLeft == direction || QBoxLayout::Direction::LeftToRight == direction) {
//        flex->setAlignment(Qt::AlignmentFlag::AlignVCenter);
//    }
    flex->setGeometry(QRect(0, 0, this->width(), this->height()));
    r_ptr.emplace_back(flex);
    return flex;
}

QLabel *QxWidget::buildLabel(const QString &text) {
    auto* label = text == "" ? new QLabel(this) : new QLabel(text, this);
    r_ptr.emplace_back(label);
    return label;
}

void QxWidget::resizeEvent(QResizeEvent *event) {
//    LOG(objectName().toStdString() + " resize ");
//    QWidget::resizeEvent(event);
//    int w = calc((QWidget *) parent(), _template["width" ].get<std::string>());
//    int h = calc((QWidget *) parent(), _template["height"].get<std::string>(), false);
//    auto size = event->size();
//    resize(size.width(), size.height());
//    auto* parent = parentWidget();
//    setGeometry(_con, 0, w, h);
}

void QxWidget::setQxWidgetGeometryByTemplate() {
    setGeometry(
            calc(parentWidget(), _template["x"].get<std::string>()),
            calc(parentWidget(), _template["y"].get<std::string>(), false),
            calc(parentWidget(), _template["width"].get<std::string>()),
            calc(parentWidget(), _template["height"].get<std::string>(), false));
//    LOG(objectName().toStdString() + " setQxWidgetGeometryByTemplate w " + std::to_string(width()) + " h " + std::to_string(height()));
}





