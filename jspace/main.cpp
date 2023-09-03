#include "QScriptFramework.h"
#include <QtCore/QDebug>
int main(int argc, char* argv[]) {
//    qDebug().noquote();
    QApplication app(argc, argv);
    RunQScript(readFile("C:\\jpro\\vtkocc\\resources\\main.js"));
    return QCoreApplication::exec();
}