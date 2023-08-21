#ifndef VTKOCC_QTTOOLS_H
#define VTKOCC_QTTOOLS_H

#include "imp.h"

class QtTools {
public:
    static void loadResources(const QString& path);
    static void printSystemFontFamily();
    static void loadFontFamily(const QString& path);
    static void setDefaultFont(const QString& font);
    static QString readFile(const QString& path);
    static inline std::string to_string(const QString& s)
    { return s.toStdString(); }
    static int calc(QWidget* p, const std::string& str, bool isVertical = false);
    /**
     * @deprecated
     */
    static inline void setColor(QWidget* p, const std::string& color)
    { p->setStyleSheet(QString("color: ").append(color.c_str()).append(";")); }
    /**
     * @deprecated
     */
    static inline void setBackgroundColor(QWidget* p, const std::string& color)
    { p->setStyleSheet(QString("background-color: ").append(color.c_str()).append(";")); }
    static inline void setBackgroundImage(QWidget* p, const std::string& path) {
        p->setStyleSheet(QString("")
            .append("background: url(").append(path.c_str()).append("); ")
            .append("background-repeat: no-repeat; ")
            .append("background-position: center; ")
        );
    }

    static bool match(const std::string& text, const std::regex& re) {
        return std::regex_match(text, re);
    }
};

#endif //VTKOCC_QTTOOLS_H
