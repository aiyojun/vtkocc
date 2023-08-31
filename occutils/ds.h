#ifndef VTKOCC_DS_H
#define VTKOCC_DS_H

#include <string>
#include <TCollection_ExtendedString.hxx>

std::string to_string(const TCollection_ExtendedString& text) {
    std::string s;
    s.resize(text.LengthOfCString());
    char *p = const_cast<char *>(s.c_str());
    text.ToUTF8CString(p);
    return s;
}

#endif //VTKOCC_DS_H
