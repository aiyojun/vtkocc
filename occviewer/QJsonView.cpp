#include "QJsonView.h"
#include "QOccWidget.h"
#include "QLinearSpinner.h"

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
    } else if (type == "QColorfulLabel") {
        js::expectString(ui, "text");
        auto text = ui["text"].get<std::string>();
        auto *label = new QColorfulLabel(QString(text.c_str()), this);
        label->setAlignment(Qt::AlignVCenter);
        addWidget(name, (QWidget *) label);
    } else if (type == "QLabel") {
        js::expectString(ui, "text");
        auto text = ui["text"].get<std::string>();
        auto *label = new QLabel(QString(text.c_str()), this);
        label->setAlignment(Qt::AlignVCenter);
        addWidget(name, (QWidget *) label);
    } else if (type == "QPushButton") {
        auto *button = new QPushButton(this);
        addWidget(name, (QWidget *) button);
    } else if (type == "QLinearSpinner") {
        auto *spinner = new QLinearSpinner(this);
        addWidget(name, (QWidget *) spinner);
    } else if (type == "QToolButton") {
        auto *button = new QToolButton(this);
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
        if (type == "QColorfulLabel") {
            auto *label = (QColorfulLabel *) widget;
            auto padding = QtTools::calcSize(0, ui["padding"].get<std::string>());
            QFontMetrics metrics(label->font());
            label->setGeometry(area.x(), area.y(), metrics.width(label->text()) + padding * 2, area.height());
        } else {
            widget->setGeometry(area.x(), area.y(), area.width(), area.height());
        }
        if (js::hasBool(ui, "visible") && !ui["visible"].get<bool>())
            widget->hide();
    }
    if (type == "QHBoxLayout") {
        bool reverse = js::hasBool(ui, "reverse") && ui["reverse"].get<bool>();
        int biasX = reverse ? (area.x() + area.width()) : area.x();
        for (auto& child : ui["children"]) {
            auto w = QtTools::calcSize(area.width() , child["width" ].get<std::string>());
            auto h = QtTools::calcSize(area.height(), child["height"].get<std::string>());
            if (js::hasString(child, "position") && child["position"].get<std::string>() == "absolute") {
                int x = js::hasString(child, "x") ? (area.x() + QtTools::calcSize(area.width() , child["x"].get<std::string>())) : area.x();
                int y = js::hasString(child, "y") ? (area.y() + QtTools::calcSize(area.height(), child["y"].get<std::string>())) : area.y();
                loopSetGeometry(child, QRect(x, y, w, h));
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
    loopSetGeometry(_ui, QRect(0, 0, size.width(), size.height()));
}


void QJsonView::setStatusBarText(QString text) {
    auto *label = (QLabel *) getWidget("statusText");
    label->setText(QString("- ").append(text));
}

void QJsonView::openLocalFileList() {
    QString filepath = QFileDialog::getOpenFileName((QWidget *) this, QStringLiteral("Select a file"));
    if (filepath.isEmpty()) return;
    emit openLocalFile(filepath);
    getWidget("occViewerSpinner")->show();
}

void QJsonView::setSidebar(QString text) {
    json j = json::parse(text.toStdString());
    //{"depth":1,"document_format":"BinXCAF","filename":"carving-machine.stp","filetype":"stp","is_assembly":true,"node_number":632}
    ((QLabel *) getWidget("clText0"))->setText(QString("Filename: ").append(j["filename"].get<std::string>().c_str()));
    ((QLabel *) getWidget("clText1"))->setText(QString("Format: ").append(j["filetype"].get<std::string>().c_str()));
    ((QLabel *) getWidget("clText2"))->setText(QString("Document: ").append(j["document_format"].get<std::string>().c_str()));
    ((QLabel *) getWidget("clText3"))->setText(QString("Parts: ").append(std::to_string(j["node_number"].get<int>()).c_str()));
    ((QLabel *) getWidget("clText4"))->setText(QString("Assembly: ").append(j["is_assembly"].get<bool>() ? "yes" : "no"));
    ((QLabel *) getWidget("clText5"))->setText(QString("Depth: ").append(std::to_string(j["depth"].get<int>()).c_str()));
    auto size = rect();
    loopSetGeometry(_ui, QRect(0, 0, size.width(), size.height()));
}

void QJsonView::hideSpinner() {
    getWidget("occViewerSpinner")->hide();
//    getWidget("occViewer")->show();
//    getWidget("occViewer")->repaint();
}

QWidget *QJsonView::getWidget(const std::string &name)  {
    if (_widgets.find(QString(name.c_str())) == _widgets.end())
        return nullptr;
    return _widgets[QString(name.c_str())];
}

void QJsonView::addWidget(const std::string &name, QWidget *p) {
    p->setObjectName(QString(name.c_str()));
    _widgets[QString(name.c_str())] = p;
}

void QJsonView::link() {
    QObject::connect((QPushButton *) getWidget("openFolder"), SIGNAL(clicked()), this, SLOT(openLocalFileList()));
    QObject::connect(this, SIGNAL(openLocalFile(QString)), _render, SLOT(importModelFile(QString)));
    QObject::connect(_render, SIGNAL(finishedReadModel()), this, SLOT(hideSpinner()));
    QObject::connect(_render, SIGNAL(sendStatusMessage(QString)), this, SLOT(setStatusBarText(QString)));
//    QObject::connect((QPushButton *) window.getWidget("projFront"), SIGNAL(clicked()),
//                     (QOccWidget *) window.getWidget("occViewer"), SLOT(projfront()));
//    QObject::connect((QPushButton *) window.getWidget("projLeft"), SIGNAL(clicked()),
//                     (QOccWidget *) window.getWidget("occViewer"), SLOT(projleft()));
//    QObject::connect((QPushButton *) window.getWidget("projTop"), SIGNAL(clicked()),
//                     (QOccWidget *) window.getWidget("occViewer"), SLOT(projtop()));
//    QObject::connect((QPushButton *) window.getWidget("openFolder"), SIGNAL(clicked()), &window,
//                     SLOT(chooseLocalFile()));
//    QObject::connect((QOccWidget *) window.getWidget("occViewer"), SIGNAL(sendStatusMessage(QString)), &window,
//                     SLOT(setStatusBarText(QString)));
//    QObject::connect((QOccWidget *) window.getWidget("occViewer"), SIGNAL(recordModelInformation(QString)), &window,
//                     SLOT(setSidebar(QString)));
//    QObject::connect((QOccWidget *) window.getWidget("occViewer"), SIGNAL(finishedLoadModel()), &window,
//                     SLOT(hideSpinner()));
}


