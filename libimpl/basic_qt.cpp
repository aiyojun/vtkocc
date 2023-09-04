#include "basic_qt.h"
#include <algorithm>
#include <regex>

int cssstyle_compute(int dis, const std::string &str) {
    std::string xStr = std::regex_replace(str, std::regex(" "), "");
    double r;
    if (std::regex_match(xStr, std::regex("^auto$"))) {
        r = -1;
    } else if (std::regex_match(xStr, std::regex("^[0-9]+px$"))) {
        r = std::stoi(xStr.substr(0, xStr.length() - 2));
    } else if (std::regex_match(xStr, std::regex("^[0-9]+%$"))) {
        r = dis * std::stod(xStr.substr(0, xStr.length() - 1)) * 0.01;
    } else if (std::regex_match(xStr, std::regex("^calc\\([0-9]+%([+-][0-9]+px)*\\)$"))) {
        size_t pos0 = xStr.find('%');
        r = dis * std::stoi(xStr.substr(5, pos0 - 5)) * 0.01 ;
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


void QtUtils::loadResources(const QString& filename) {
    QResource::registerResource(filename);
}

void QtUtils::printSystemFontsSupport() {
    QFontDatabase fontBase;
    foreach (const QString &fontFamily, fontBase.families()) {
        LOG(fontFamily.toStdString());
    }
}

int QtUtils::loadFontFamily(const QString &path) {
    return QFontDatabase::addApplicationFont(path);
}

void QtUtils::setDefaultFont(const QString &font) {
    QApplication::setFont(QFont(font));
}

QString QtUtils::readFile(const QString &path) {
    QFile file(path);
    QString r;
    if (file.exists()) {
        file.open(QFile::OpenModeFlag::ReadOnly);
        r = QString(file.readAll());
        file.close();
    }
    return r;
}