#include "QScriptFramework.h"
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    RunQScript(readFile("C:\\jpro\\vtkocc\\resources\\main.js"));
    return QCoreApplication::exec();
}