#include "imp.h"

std::string toLowerCase(const std::string& text)
{ std::string copy(text); std::transform(
            copy.begin(), copy.end(),
            copy.begin(), ::tolower);
    return copy; }
std::string toUpperCase(const std::string& text)
{ std::string copy(text); std::transform(
            copy.begin(), copy.end(),
            copy.begin(), ::toupper);
    return copy; }