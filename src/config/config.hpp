#ifndef __CONFIG_HPP
#define __CONFIG_HPP

#include "yaml-cpp/yaml.h"

#include <string>
#include <vector>

#define DEFAULT_CONFIG_FILENAME "./config.yaml"

class configDataType {
public:
    std::string name    = "";
    int         age     = 0;
    double      grade   = 0;
    bool        isHuman = false;

    std::vector<int> numbers;
};

class configType {
public:
    configType();
    configType(std::string filename);
    ~configType();

    static configType &Instance() {
        static configType _instance;
        return _instance;
    }

    void read_config_file(std::string filename);
    void read_config_file();

    void save_config_file(std::string filename);
    void save_config_file();

    void print_config();

    configDataType data;

private:
    int mkdirs(std::string path, mode_t mode);

    std::string m_filename = DEFAULT_CONFIG_FILENAME;
};

#endif