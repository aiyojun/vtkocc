#include "QxWidget.h"
#include "json.hpp"
#include "imp.h"

using nlohmann::json;

QxWidget::QxWidget(QWidget *parent) {

}

QWidget* lparse(const json& root, QWidget* parent, std::map<std::string, QWidget *>& container) {
    auto *p = new QWidget(parent);
    if (!root.contains("name"))
        throw std::runtime_error("widget lack of name");
    std::string name = to_string(root["name"]);
    name = name.substr(1, name.length() - 2);
    std::string background = root.contains("background") ? to_string(root["background"]) : "white";
    auto *title = new QLabel(p);
    title->setText(name.c_str());
    title->setAlignment(Qt::AlignCenter);
    auto x = root["x"].get<int>();
    auto y = root["y"].get<int>();
    auto width  = root["width" ].get<int>();
    auto height = root["height"].get<int>();
//    p->setGeometry(x, y, width, height);
//    p->setBaseSize(width, height);
    p->setFixedSize(width, height);
    LOG("-- " + name + " width " + std::to_string(width) + " height " + std::to_string(height));
    if (container.find(name) != container.end())
        throw std::runtime_error("repeat widget name");
    container[name] = p;
    auto qStyle = std::string("background-color:").append(background).append(";");
    p->setStyleSheet(qStyle.c_str());
    auto flex = new QBoxLayout(QBoxLayout::Direction::TopToBottom, p);
    flex->setSpacing(0);
    flex->setMargin(0);
//    flex->setGeometry(QRect(x, y, x+width, y+height));
//    flex->setAlignment();
    for (auto &child: root["children"]) {
        auto *q = lparse(child, p, container);
        flex->addWidget(q);
    }
    return p;
}


QWidget *QxWidget::parse(
        const QString &text,
        QWidget* parent,
        std::map<std::string, QWidget *>& pool
        ) {
    auto root = json::parse(text.toStdString());
    return lparse(root, parent, pool);
}
