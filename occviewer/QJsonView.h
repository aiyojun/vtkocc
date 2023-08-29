#ifndef VTKOCC_QJSONVIEW_H
#define VTKOCC_QJSONVIEW_H

#include "imp.h"
#include "json.hpp"
#include "QRenderThread.h"

using nlohmann::json;

class JvContext {
public:
    const json& ui;
    QRect area;
    JvContext(const json& ui, QRect a): ui(ui), area(a) {}
};

class QColorfulLabel : public QLabel {
    Q_OBJECT
public:
    explicit QColorfulLabel(QWidget* parent = nullptr): QLabel(parent) {}
    explicit QColorfulLabel(QString text, QWidget* parent = nullptr): QLabel(std::move(text), parent) {}
    ~QColorfulLabel() override = default;
};

class QJsonView : public QMainWindow {
    Q_OBJECT
public:
    explicit QJsonView(QRenderThread* r, QWidget* parent = nullptr): QMainWindow(parent), _render(r) {}
    ~QJsonView() override = default;
    void parse(JvContext context);
    void loopSetGeometry(const json& ui, QRect area);
    void traverse(const json& ui, std::function<void (const json&)> callback);
    void setUi(const json& j) { this->_ui = j;}
    QWidget *getWidget(const std::string& name);
    void link();
Q_SIGNALS:
    void openLocalFile(QString filename);
public Q_SLOTS:
    void setStatusBarText(QString text);
    void openLocalFileList();
    void setSidebar(QString text);
    void hideSpinner();
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    void addWidget(const std::string& name, QWidget* p);
private:
    json _ui;
    QMap<QString, QWidget *> _widgets;
    QRenderThread* _render;
};


#endif //VTKOCC_QJSONVIEW_H
