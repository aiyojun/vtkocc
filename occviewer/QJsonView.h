#ifndef VTKOCC_QJSONVIEW_H
#define VTKOCC_QJSONVIEW_H

#include "imp.h"
#include "json.hpp"

using nlohmann::json;

class JvContext {
public:
    const json& ui;
    QRect area;
    JvContext(const json& ui, QRect a): ui(ui), area(a) {}
};

class QJsonView : public QMainWindow {
    Q_OBJECT
public:
    explicit QJsonView(QWidget* parent = nullptr): QMainWindow(parent) {}
    ~QJsonView() override = default;
    void parse(JvContext context);
    void loopSetGeometry(const json& ui, QRect area);
    void traverse(const json& ui, std::function<void (const json&)> callback);
    void setui(const json& j) {this->ui = j;}
    QWidget *getWidget(const std::string& name) {
        if (pool.find(QString(name.c_str())) == pool.end())
            return nullptr;
        return pool[QString(name.c_str())];
    }
Q_SIGNALS:
public Q_SLOTS:
    void setstatusbar(QString text);
    void chooseLocalFile();
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    void addWidget(const std::string& name, QWidget* p) {
        p->setObjectName(QString(name.c_str()));
        pool[QString(name.c_str())] = p; }
    QMap<QString, QWidget*> pool;
    json ui;
};


#endif //VTKOCC_QJSONVIEW_H
