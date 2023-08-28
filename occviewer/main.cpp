#include "imp.h"
#include "QJsonView.h"
#include "json.hpp"
using nlohmann::json;

#include "QOccWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QThreadPool::globalInstance()->setMaxThreadCount(3);
//    json cfg = json::parse(QtTools::readFile("vtkocc.config.json").toStdString());
    QtTools::loadResources("rsrcs.rcc");
    QtTools::loadFontFamily(":/titillium-web-font/TitilliumWeb-1eq2.ttf");
    QtTools::setDefaultFont("Titillium Web");
    QJsonView window;
    window.setWindowIcon(QIcon(":/icons/3d.svg"));
    window.setStyleSheet(QtTools::readFile(QString(":/ui.qss")));
    auto j = json::parse(QtTools::readFile(QString(":/ui.json")).toStdString());
    window.setWindowTitle(QString(j["window-title"].get<std::string>().c_str()));
    window.setui(j);
    QRect beginPos(0, 0, QtTools::calcSize(0, j["width"].get<std::string>()), QtTools::calcSize(0, j["height"].get<std::string>()));
    try {
        window.parse(JvContext(j, beginPos));
        window.loopSetGeometry(j, beginPos);
        window.resize(beginPos.width(), beginPos.height());
    } catch (std::exception &e) {
        Message::SendFail() << e.what();
    }
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
    QObject::connect((QOccWidget *) window.getWidget("occViewer"), SIGNAL(recordModelInformation(QString)), &window,
                     SLOT(setSidebar(QString)));
    QObject::connect((QOccWidget *) window.getWidget("occViewer"), SIGNAL(finishedLoadModel()), &window,
                     SLOT(hideSpinner()));
    window.show();
    return QApplication::exec();
}