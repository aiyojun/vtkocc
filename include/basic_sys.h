#ifndef VTKOCC_BASIC_TOOL_H
#define VTKOCC_BASIC_TOOL_H

#include <string>

/** path related */
std::string dirname(const std::string &filepath);

std::string basename(const std::string &filepath);

/** string related */
std::string to_lowercase(const std::string &text);

std::string to_uppercase(const std::string &text);

/** regex related */
bool match(const std::string &text, const std::string &regex_string);

/** fs: file read */
std::string read_file(const char *filename);

void write_file(const char *filename, const std::string &text);

void append_file(const char *filename, const std::string &text);

#endif //VTKOCC_BASIC_TOOL_H
