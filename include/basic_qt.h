#ifndef VTKOCC_BASIC_QT_H
#define VTKOCC_BASIC_QT_H

#include "import_cpp.h"
#include "import_qt.h"

int cssstyle_compute(int real_length, const std::string &calc_string);

class QtUtils {
public:
    static void loadResources(const QString &filename);

    static void printSystemFontsSupport();

    static int loadFontFamily(const QString &path);

    static void setDefaultFont(const QString &font);

    static QString readFile(const QString &path);
};

#endif //VTKOCC_BASIC_QT_H
