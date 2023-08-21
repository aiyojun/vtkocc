#include "QJsonView.h"
#include "QOccWidget.h"

namespace js {

    void exists(const json& j, const std::string& p) {
        if (!j.contains(p))
            throw std::runtime_error("lack of property : " + to_string(j));
    }

    void expectString(const json& j, const std::string& p) {
        exists(j, p);
        if (!j.is_string())
            throw std::runtime_error("expect string, but data is " + to_string(j));
    }

    void expectInteger(const json& j, const std::string& p) {
        exists(j, p);
        if (!j.is_number_integer())
            throw std::runtime_error("expect integer, but data is " + to_string(j));
    }

    void expectDouble(const json& j, const std::string& p) {
        exists(j, p);
        if (!j.is_number_float())
            throw std::runtime_error("expect float, but data is " + to_string(j));
    }

    void expectArray(const json& j, const std::string& p) {
        exists(j, p);
        if (!j.is_array())
            throw std::runtime_error("expect array, but data is " + to_string(j));
    }

    void expectObject(const json& j, const std::string& p) {
        exists(j, p);
        if (!j.is_object())
            throw std::runtime_error("expect object, but data is " + to_string(j));
    }

}

QWidget* QJsonView::parse(JvContext context) {
    auto &ui = context.ui;
    auto &area = context.area;
    js::expectString(ui, "name");
    js::expectString(ui, "type");
    auto name = ui["name"].get<std::string>();
    auto type = ui["type"].get<std::string>();
    QWidget* r;
    if (type == "QHBoxLayout") {
        js::expectArray(ui, "children");
        auto* layout = new QHBoxLayout(context.parent);
        r = (QWidget *) layout;
        addWidget(name, r);
        int biasX = area.x();
        for (auto& child : ui["children"]) {
            js::expectString(child, "width" );
            js::expectString(child, "height");
            auto w = QtTools::calc(r, child["width" ].get<std::string>());
            auto h = QtTools::calc(r, child["height"].get<std::string>());
            auto *p = parse(JvContext(child, r, QRect(biasX, area.y(), w, h)));
            p->resize(w, h);
            layout->addWidget(p);
            biasX += w;
        }
    } else if (type == "QVBoxLayout") {
        js::expectArray(ui, "children");
        auto* layout = new QVBoxLayout(context.parent);
        r = (QWidget *) layout;
        addWidget(name, r);
        int biasY = area.y();
        for (auto& child : ui["children"]) {
            js::expectString(child, "width" );
            js::expectString(child, "height");
            auto w = QtTools::calc(r, child["width" ].get<std::string>());
            auto h = QtTools::calc(r, child["height"].get<std::string>());
            auto *p = parse(JvContext(child, r, QRect(area.x(), biasY, w, h)));
            p->resize(w, h);
            layout->addWidget(p);
            biasY += w;
        }
    } else if (type == "QOccWidget") {
        auto *widget = new QOccWidget(context.parent);
        addWidget(name, r);
        r = (QWidget *) widget;
    } else if (type == "QLabel") {
        js::expectString(ui, "text");
        auto text = ui["text"].get<std::string>();
        auto *label = new QLabel(QString(text.c_str()), context.parent);
        r = (QWidget *) label;
        addWidget(name, r);
    } else {
        throw std::runtime_error("No such QWidget : " + type);
    }
    r->setObjectName(name.c_str());
    return r;
}

