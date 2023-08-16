#include "QtTools.h"

void QtTools::loadResources(const QString &path) {
    QResource::registerResource(path);
}

void QtTools::printSystemFontFamily() {
    QFontDatabase fontBase;
    foreach (const QString &fontFamily, fontBase.families()) {
        LOG(fontFamily.toStdString());
    }
}

void QtTools::loadFontFamily(const QString& path) {
    int fontId = QFontDatabase::addApplicationFont(path);
    if (fontId < 0)
        throw std::runtime_error("No such file : " + path.toStdString());
    QFontDatabase::applicationFontFamilies(fontId).at(0);
}

void QtTools::setDefaultFont(const QString &font) {
    QApplication::setFont(QFont(font));
}

QString QtTools::readFile(const QString &path) {
    QFile file(path);
    QString r;
    if (file.exists()) {
        file.open(QFile::OpenModeFlag::ReadOnly);
        r = QString(file.readAll());
        file.close();
    }
    return r;
}



