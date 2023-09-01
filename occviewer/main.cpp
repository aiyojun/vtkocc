#include "imp.h"
#include "QJsonView.h"
#include "json.hpp"
using nlohmann::json;
#include "QOccWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QRenderThread render;
    render.startLoopRender();
    qDebug() << "-- Run render thread";
//    QThreadPool::globalInstance()->setMaxThreadCount(3);
//    json cfg = json::parse(QtTools::readFile("vtkocc.config.json").toStdString());
    QtTools::loadResources("rsrcs.rcc");
    QtTools::loadFontFamily(":/titillium-web-font/TitilliumWeb-1eq2.ttf");
    QtTools::setDefaultFont("Titillium Web");
    auto j = json::parse(QtTools::readFile(QString(":/ui.json")).toStdString());
    QJsonView window(j, &render);
    window.setWindowIcon(QIcon(":/icons/3d.svg"));
    window.setStyleSheet(QtTools::readFile(QString(":/ui.qss")));
    window.setWindowTitle(QString(j["window-title"].get<std::string>().c_str()));
    window.show();
    render.onResize();
    qDebug() << "-- Enter events loop ...";
    return QApplication::exec();
}