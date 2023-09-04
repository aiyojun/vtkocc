#include "QScriptFramework.h"
#include "basic_qt.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QtUtils::loadResources("rsrcs.rcc");
    QString filename("resources/main.js");
    QFileSystemWatcher watcher;
    watcher.addPath(filename);
    QApplicationWindow window(filename);
    QObject::connect(
        &watcher,
        SIGNAL(fileChanged(QString)),
        &window,
        SLOT(hotReload())
    );
    window.show();
//    RunQScript(readFile(":/main.js"));
    return QCoreApplication::exec();
}