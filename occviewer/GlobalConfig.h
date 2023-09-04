#ifndef VTKOCC_GLOBALCONFIG_H
#define VTKOCC_GLOBALCONFIG_H

#include "basic_sys.h"
#include "json.hpp"

using nlohmann::json;

class GlobalConfig {
public:
    static void build(const char *filename) { _instance = new GlobalConfig(filename); }

    static const GlobalConfig &getInstance() { return *_instance; }

    ~GlobalConfig() { delete _instance; _instance = nullptr; }

    template<typename T> T get(const std::string k) { return _config.get<T>(k); }

private:
    GlobalConfig(const char *filename) { _config = json::parse(read_file(filename)); }

    json _config;

    static GlobalConfig *_instance;
};

#endif //VTKOCC_GLOBALCONFIG_H
