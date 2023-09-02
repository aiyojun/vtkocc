#include "QScriptFramework.h"

QString readFile(const QString &path) {
    QFile file(path);
    QString r;
    if (file.exists()) {
        file.open(QFile::OpenModeFlag::ReadOnly);
        r = QString(file.readAll());
        file.close();
    }
    return r;
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    executeScript(readFile("C:\\jpro\\vtkocc\\resources\\main.js"));
    return QCoreApplication::exec();
}