#include "QScriptFramework.h"
#include "basic_qt.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QtUtils::loadResources("rsrcs.rcc");
//    if (argc < 2) {
//        qDebug() << "Please specify a runnable javascript file.";
//        return 1;
//    }
    QString filename(argv[1]);
    qDebug() << "Run javascript file : " << filename;
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