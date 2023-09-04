#include "basic_sys.h"
#include "basic_json.h"
#include <regex>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

std::string dirname(const std::string& filepath) {
    int pos = std::max((int) filepath.find_last_of('/'), (int) filepath.find_last_of('\\'));
    return filepath.substr(0, pos);
}

std::string basename(const std::string& filepath) {
    int pos = std::max((int) filepath.find_last_of('/'), (int) filepath.find_last_of('\\'));
    return filepath.substr(pos + 1);
}

bool match(const std::string& text, const std::string& regex_string) {
    return std::regex_match(text, std::regex(regex_string));
}

void write_file(const char *filename, const std::string& text) {
    std::ofstream file_stream(filename, std::ios::out);
    file_stream.write(text.c_str(), text.length());
    file_stream.close();
}

void append_file(const char *filename, const std::string& text) {
    std::ofstream file_stream(filename, std::ios::app);
    file_stream.write(text.c_str(), text.length());
    file_stream.close();
}

std::string read_file(const char *filename) {
    std::string text, _t;
    std::ifstream file_stream(filename, std::ios::in);
    if (!file_stream.is_open()) return "";
    while (std::getline(file_stream, _t)) { text.append(_t).append("\n"); }
    file_stream.close();
    return text;
}

std::string to_lowercase(const std::string& text)
{ std::string copy(text); std::transform(
            copy.begin(), copy.end(),
            copy.begin(), ::tolower);
    return copy; }

std::string to_uppercase(const std::string& text)
{ std::string copy(text); std::transform(
            copy.begin(), copy.end(),
            copy.begin(), ::toupper);
    return copy; }

/** json */

namespace js {
    void expect(const json &j, const std::string &p) {
        if (!j.contains(p))
            throw std::runtime_error("property " + p + ", lack of property : " + to_string(j));
    }

    void expect_boolean(const json &j, const std::string &p) {
        expect(j, p);
        if (!j[p].is_boolean())
            throw std::runtime_error("property " + p + ", expect boolean, but data is " + to_string(j));
    }

    void expect_string(const json &j, const std::string &p) {
        expect(j, p);
        if (!j[p].is_string())
            throw std::runtime_error("property " + p + ", expect string, but data is " + to_string(j));
    }

    void expect_integer(const json &j, const std::string &p) {
        expect(j, p);
        if (!j[p].is_number_integer())
            throw std::runtime_error("property " + p + ", expect integer, but data is " + to_string(j));
    }

    void expect_double(const json &j, const std::string &p) {
        expect(j, p);
        if (!j[p].is_number_float())
            throw std::runtime_error("property " + p + ", expect float, but data is " + to_string(j));
    }

    void expect_array(const json &j, const std::string &p) {
        expect(j, p);
        if (!j[p].is_array())
            throw std::runtime_error("property " + p + ", expect array, but data is " + to_string(j));
    }

    void expect_object(const json &j, const std::string &p) {
        expect(j, p);
        if (!j[p].is_object())
            throw std::runtime_error("property " + p + ", expect object, but data is " + to_string(j));
    }

    std::string get_string(const json &j, const std::string &p) {
        return j[p].get<std::string>();
    }

    int get_integer(const json &j, const std::string &p) {
        return j[p].get<int>();
    }

    double get_double(const json &j, const std::string &p) {
        return j[p].get<double>();
    }

    bool get_boolean(const json &j, const std::string &p) {
        return j[p].get<bool>();
    }

    bool has_number(const json &j, const std::string &p) {
        return j.contains(p) && j[p].is_number();
    }

    bool has_string(const json &j, const std::string &p) {
        return j.contains(p) && j[p].is_string();
    }

    bool has_array(const json &j, const std::string &p) {
        return j.contains(p) && j[p].is_array();
    }

    bool has_object(const json &j, const std::string &p) {
        return j.contains(p) && j[p].is_object();
    }

    bool has_boolean(const json &j, const std::string &p) {
        return j.contains(p) && j[p].is_boolean();
    }
}