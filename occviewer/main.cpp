#include "imp.h"
#include "QJsonView.h"
#include "json.hpp"

using nlohmann::json;

#include "QOccWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    json cfg = json::parse(QtTools::readFile("vtkocc.config.json").toStdString());
    QtTools::loadResources("rsrcs.rcc");
    QtTools::loadFontFamily(":/titillium-web-font/TitilliumWeb-1eq2.ttf");
    QtTools::setDefaultFont("Titillium Web");
    QJsonView window;
    window.setStyleSheet(QtTools::readFile(QString(":/ui.qss")));
    auto j = json::parse(QtTools::readFile(QString(":/ui.json")).toStdString());
    window.setui(j);
    QRect beginPos(0, 0, 900, 600);
    try {
        window.parse(JvContext(j, beginPos));
        window.loopSetGeometry(j, beginPos);
        window.resize(beginPos.width(), beginPos.height());
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
//    auto *occViewer = (QOccWidget *) window.getWidget("occViewer");
//    auto path = "C:\\Users\\jun.dai\\Desktop\\modelstep3d\\xxx_01.STL"; //"C:\\jpro\\vtkocc\\r8.stl"
//    QModelReader reader(cfg["model"].get<std::string>().c_str(), occViewer->refShapes());
    QObject::connect((QPushButton *) window.getWidget("projFront"), SIGNAL(clicked()),
                     (QOccWidget *) window.getWidget("occViewer"), SLOT(projfront()));
    QObject::connect((QPushButton *) window.getWidget("projLeft"), SIGNAL(clicked()),
                     (QOccWidget *) window.getWidget("occViewer"), SLOT(projleft()));
    QObject::connect((QPushButton *) window.getWidget("projTop"), SIGNAL(clicked()),
                     (QOccWidget *) window.getWidget("occViewer"), SLOT(projtop()));
    QObject::connect((QPushButton *) window.getWidget("openFolder"), SIGNAL(clicked()), &window,
                     SLOT(chooseLocalFile()));
    QObject::connect((QOccWidget *) window.getWidget("occViewer"), SIGNAL(sendStatusMessage(QString)), &window,
                     SLOT(setstatusbar(QString)));
//    QObject::connect(&reader, SIGNAL(complete()), occViewer, SLOT(loadShapes()));
//    reader.start(QThread::HighPriority);
    window.show();
    return QApplication::exec();
}