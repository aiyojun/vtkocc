#ifndef VTKOCC_QJSONVIEW_H
#define VTKOCC_QJSONVIEW_H

#include "imp.h"
#include "QRenderThread.h"
#include "QNavigator.h"
#include "json.hpp"

using nlohmann::json;

class JvContext {
public:
    const json &ui;
    QRect area;

    JvContext(const json &ui, QRect a) : ui(ui), area(a) {}
};

class QColorfulLabel : public QLabel {
Q_OBJECT
public:
    explicit QColorfulLabel(QWidget *parent = nullptr);

    explicit QColorfulLabel(const QString& text, QWidget *parent = nullptr) : QLabel(text, parent) {}

    ~QColorfulLabel() override = default;
};

class QJsonView : public QMainWindow {
Q_OBJECT
public:
    explicit QJsonView(const json &ui, QRenderThread *r, QWidget *parent = nullptr);

    ~QJsonView() override = default;

    QWidget *getWidget(const std::string &name);

Q_SIGNALS:

    void openLocalFile(QString filename);

public Q_SLOTS:

    void setStatusBarText(QString text);

    void openLocalFileList();

    void setSidebar(QString text);

    void hideSpinner();

    void setAssemblyTree(QString text);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void addWidget(const std::string &name, QWidget *p);

    void parse(JvContext context);

    void loopSetGeometry(const json &ui, QRect area);

    void traverse(const json &ui, std::function<void(const json &)> callback);

    void link();

    Navigation *loopParseTree(const json &node, int depth = 0);

private:
    json _ui;
    QMap<QString, QWidget *> _widgets;
    QRenderThread *_render;
};


#endif //VTKOCC_QJSONVIEW_H
