#ifndef VTKOCC_QJSONVIEW_H
#define VTKOCC_QJSONVIEW_H

#include "imp.h"
#include "json.hpp"

using nlohmann::json;

class JvContext {
public:
    const json& ui;
    QWidget* parent;
    QRect area;
    JvContext(const json& ui, QWidget* p, QRect a): ui(ui), parent(p), area(a) {}
};

class QJsonView : QMainWindow {
    Q_OBJECT
public:
    explicit QJsonView(QWidget* parent = nullptr): QMainWindow(parent) {}
    ~QJsonView() override = default;
    QWidget* parse(JvContext context);
private:
    inline void addWidget(const std::string& name, QWidget* p) { pool[QString(name.c_str())] = p; }
    QMap<QString, QWidget*> pool;
};


#endif //VTKOCC_QJSONVIEW_H
