#include "QJsonView.h"
#include "QOccWidget.h"
#include "QModelReader.h"

namespace js {

    void exists(const json& j, const std::string& p) {
        if (!j.contains(p))
            throw std::runtime_error("property " + p + ", lack of property : " + to_string(j));
    }

    void expectString(const json& j, const std::string& p) {
        exists(j, p);
        if (!j[p].is_string())
            throw std::runtime_error("property " + p + ", expect string, but data is " + to_string(j));
    }

    void expectInteger(const json& j, const std::string& p) {
        exists(j, p);
        if (!j[p].is_number_integer())
            throw std::runtime_error("property " + p + ", expect integer, but data is " + to_string(j));
    }

    void expectDouble(const json& j, const std::string& p) {
        exists(j, p);
        if (!j[p].is_number_float())
            throw std::runtime_error("property " + p + ", expect float, but data is " + to_string(j));
    }

    void expectArray(const json& j, const std::string& p) {
        exists(j, p);
        if (!j[p].is_array())
            throw std::runtime_error("property " + p + ", expect array, but data is " + to_string(j));
    }

    void expectObject(const json& j, const std::string& p) {
        exists(j, p);
        if (!j[p].is_object())
            throw std::runtime_error("property " + p + ", expect object, but data is " + to_string(j));
    }

    bool hasString(const json& j, const std::string& p) {
        return j.contains(p) && j[p].is_string();
    }

    bool hasBool(const json& j, const std::string& p) {
        return j.contains(p) && j[p].is_boolean();
    }

}

void QJsonView::parse(JvContext context) {
    auto &ui = context.ui;
    auto &area = context.area;
    js::expectString(ui, "name");
    js::expectString(ui, "type");
    auto name = ui["name"].get<std::string>();
    auto type = ui["type"].get<std::string>();
    if (type == "QHBoxLayout") {
        js::expectArray(ui, "children");
        int biasX = area.x();
        for (auto& child : ui["children"]) {
            js::expectString(child, "width" );
            js::expectString(child, "height");
            auto w = QtTools::calcSize(area.width() , child["width" ].get<std::string>());
            auto h = QtTools::calcSize(area.height(), child["height"].get<std::string>());
            parse(JvContext(child, QRect(biasX, area.y(), w, h)));
            biasX += w;
        }
    } else if (type == "QVBoxLayout") {
        js::expectArray(ui, "children");
        int biasY = area.y();
        for (auto& child : ui["children"]) {
            js::expectString(child, "width" );
            js::expectString(child, "height");
            auto w = QtTools::calcSize(area.width() , child["width" ].get<std::string>());
            auto h = QtTools::calcSize(area.height(), child["height"].get<std::string>());
            parse(JvContext(child, QRect(area.x(), biasY, w, h)));
            biasY += h;
        }
    } else if (type == "QOccWidget") {
        auto *widget = new QOccWidget(this);
        addWidget(name, (QWidget *) widget);
    } else if (type == "QLabel") {
        js::expectString(ui, "text");
        auto text = ui["text"].get<std::string>();
        auto *label = new QLabel(QString(text.c_str()), this);
        label->setAlignment(Qt::AlignVCenter);
        addWidget(name, (QWidget *) label);
    } else if (type == "QPushButton") {
        auto *button = new QPushButton(this);
        addWidget(name, (QWidget *) button);
    } else if (type == "QLineEdit") {
        auto *input = new QLineEdit(this);
        if (js::hasString(ui, "placeholder"))
            input->setPlaceholderText(ui["placeholder"].get<std::string>().c_str());
        addWidget(name, (QWidget *) input);
    } else if (type == "QFrame") {
        auto *frame = new QFrame(this);
        addWidget(name, (QWidget *) frame);
    } else {
        throw std::runtime_error("No such QWidget : " + type);
    }
}

void QJsonView::loopSetGeometry(const json& ui, QRect area) {
    auto name = ui["name"].get<std::string>();
    auto type = ui["type"].get<std::string>();
    auto *widget = getWidget(name);
    if (widget != nullptr) {
        widget->setGeometry(area.x(), area.y(), area.width(), area.height());
    }
    if (type == "QHBoxLayout") {
        bool reverse = js::hasBool(ui, "reverse") && ui["reverse"].get<bool>();
        int biasX = reverse ? (area.x() + area.width()) : area.x();
        for (auto& child : ui["children"]) {
            auto w = QtTools::calcSize(area.width() , child["width" ].get<std::string>());
            auto h = QtTools::calcSize(area.height(), child["height"].get<std::string>());
            if (js::hasString(child, "position") && child["position"].get<std::string>() == "absolute") {
                loopSetGeometry(child, QRect(area.x(), area.y(), w, h));
                continue;
            }
            loopSetGeometry(child, QRect(reverse ? (biasX - w) : biasX, area.y(), w, h));
            biasX += reverse ? (-w) : w;
        }
    } else if (type == "QVBoxLayout") {
        bool reverse = js::hasBool(ui, "reverse") && ui["reverse"].get<bool>();
        int biasY = area.y();
        for (auto& child : ui["children"]) {
            auto w = QtTools::calcSize(area.width() , child["width" ].get<std::string>());
            auto h = QtTools::calcSize(area.height(), child["height"].get<std::string>());
            if (js::hasString(child, "position") && child["position"].get<std::string>() == "absolute") {
                loopSetGeometry(child, QRect(area.x(), area.y(), w, h));
                continue;
            }
            loopSetGeometry(child, QRect(area.x(), reverse ? (biasY - h) : biasY, w, h));
            biasY += reverse ? (-h) : h;
        }
    }
}

void QJsonView::traverse(const json &ui, std::function<void(const json &)> callback) {
    callback(ui);
    auto type = ui["type"].get<std::string>();
    if (!std::regex_match(type, std::regex(".*Layout$")))
        return;
    for (auto& child : ui["children"]) {
        traverse(child, callback);
    }
}

void QJsonView::resizeEvent(QResizeEvent *event) {
//    QWidget::resizeEvent(event);
    auto size = event->size();
    loopSetGeometry(ui, QRect(0, 0, size.width(), size.height()));
}


void QJsonView::setstatusbar(QString text) {
    auto *label = (QLabel *) getWidget("statusText");
    label->setText(QString("- ").append(text));
}

void QJsonView::chooseLocalFile() {
    QString filepath = QFileDialog::getOpenFileName(this, QStringLiteral("Select a file"));
    LOG("-- Select file : " + filepath.toStdString());
    auto *occViewer = (QOccWidget *) getWidget("occViewer");
    delete reader;
    reader = new QModelReader(filepath, occViewer->refShapes());
    reader->start(QThread::HighPriority);
    QObject::connect(reader, SIGNAL(complete()), occViewer, SLOT(loadShapes()));
    LOG("Reading " + filepath.toStdString() + "...");
    setstatusbar("Reading " + filepath + "...");
}
