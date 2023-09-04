#include "QJsonWidget.h"
#include "QOccWidget.h"
#include "json.hpp"
#include "basic_qt.h"

using nlohmann::json;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QRenderThread render;
    render.startLoopRender();
    qDebug() << "-- Run render thread";
//    QThreadPool::globalInstance()->setMaxThreadCount(3);
//    json cfg = json::parse(QtTools::readFile("vtkocc.config.json").toStdString());
    QtUtils::loadResources("rsrcs.rcc");
    QtUtils::loadFontFamily(":/titillium-web-font/TitilliumWeb-1eq2.ttf");
    QtUtils::setDefaultFont("Titillium Web");
    auto j = json::parse(QtUtils::readFile(QString(":/ui.json")).toStdString());
    QJsonWidget window(j, &render);
    window.setWindowIcon(QIcon(":/icons/3d.svg"));
    window.setStyleSheet(QtUtils::readFile(QString(":/ui.qss")));
    window.setWindowTitle(QString(j["window-title"].get<std::string>().c_str()));
    window.show();
    render.onResize();
    qDebug() << "-- Enter events loop ...";
    return QApplication::exec();
}