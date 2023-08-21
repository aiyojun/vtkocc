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

int QtTools::calc(QWidget* p, const std::string& str, bool isVertical) {
    std::string xStr = std::regex_replace(str, std::regex(" "), "");
    double r;
    if (std::regex_match(xStr, std::regex("^[0-9]+px$"))) {
        r = std::stoi(xStr.substr(0, xStr.length() - 2));
    } else if (std::regex_match(xStr, std::regex("^[0-9]+%$"))) {
        r = (isVertical ? p->width() : p->height()) * std::stod(xStr.substr(0, xStr.length() - 1)) * 0.01;
    } else if (std::regex_match(xStr, std::regex("^calc\\([0-9]+%([+-][0-9]+px)*\\)$"))) {
        size_t pos0 = xStr.find('%');
        r = (isVertical ? p->width() : p->height()) * std::stoi(xStr.substr(5, pos0 - 5)) * 0.01 ;
        std::string rest = xStr.substr(pos0 + 1, xStr.length() - pos0 - 2);
        while (rest.length() > 0) {
            size_t pos = rest.find("px");
            if (pos == std::string::npos)
                break;
            r += std::stoi(rest.substr(0, pos));
            rest = rest.substr(pos + 2);
        }
    } else if (std::regex_match(xStr, std::regex("^[0]+$"))) {
        r = 0;
    } else
        throw std::runtime_error("error distance unit : " + xStr);
    return (int) r;
}



