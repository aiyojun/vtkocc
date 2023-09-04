#ifndef VTKOCC_BASIC_JSON_H
#define VTKOCC_BASIC_JSON_H

#include <string>
#include "json.hpp"

using nlohmann::json;

namespace js {
    void expect(const json &j, const std::string &p);

    void expect_boolean(const json &j, const std::string &p);

    void expect_string(const json &j, const std::string &p);

    void expect_integer(const json &j, const std::string &p);

    void expect_double(const json &j, const std::string &p);

    void expect_array(const json &j, const std::string &p);

    void expect_object(const json &j, const std::string &p);

    std::string get_string(const json &j, const std::string &p);

    int get_integer(const json &j, const std::string &p);

    double get_double(const json &j, const std::string &p);

    bool get_boolean(const json &j, const std::string &p);

    bool has_number(const json &j, const std::string &p);

    bool has_string(const json &j, const std::string &p);

    bool has_array(const json &j, const std::string &p);

    bool has_object(const json &j, const std::string &p);

    bool has_boolean(const json &j, const std::string &p);
}

#endif //VTKOCC_BASIC_JSON_H
