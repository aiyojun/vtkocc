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

    QJsonView window(&render);
    window.setWindowIcon(QIcon(":/icons/3d.svg"));
    window.setStyleSheet(QtTools::readFile(QString(":/ui.qss")));
    auto j = json::parse(QtTools::readFile(QString(":/ui.json")).toStdString());

    qDebug() << "-- Parsing ui.json";

    window.setWindowTitle(QString(j["window-title"].get<std::string>().c_str()));
    window.setUi(j);
    QRect beginPos(0, 0,
                   QtTools::calcSize(0, j["width"].get<std::string>()),
                   QtTools::calcSize(0, j["height"].get<std::string>()));
    try {
        window.parse(JvContext(j, beginPos));

        QOccWidget *viewer = (QOccWidget *) window.getWidget("occViewer");
        viewer->setRender(&render);
        qDebug() << "-- Prepare opengl context";
        render.onCreate((void *) (viewer->winId()));

        window.loopSetGeometry(j, beginPos);
        window.resize(beginPos.width(), beginPos.height());
    } catch (std::exception &e) {
        Message::SendFail() << e.what();
    }

    qDebug() << "-- Prepare Qt signal-slot";
    window.link();
    window.show();
    render.onResize();

    qDebug() << "-- Enter events loop ...";

    return QApplication::exec();
}