//
// Created by jun.dai on 2023/8/16.
//

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
};

#endif //VTKOCC_QTTOOLS_H
