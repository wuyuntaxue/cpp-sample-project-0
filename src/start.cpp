#include "config/config.hpp"
#include "log/log.hpp"

#include <iostream>

int main() {
    std::cout << "taxue sample start" << std::endl;
    log_init(); // 初始化spd日志
    LOG_INFO("start run ... ...");

    // 读写yaml配置文件
    configType::Instance().read_config_file("./config.yaml");
    configType::Instance().print_config();

    configType::Instance().data.name += "a";
    configType::Instance().data.age += 1;
    configType::Instance().data.grade += 1.1;
    configType::Instance().data.isHuman = !configType::Instance().data.isHuman;
    configType::Instance().data.numbers.push_back(100);

    configType::Instance().save_config_file();

    // base64_test();

    LOG_WARN("sample project done, goodbye(^_^)\n......");
    log_drop(); // 释放日志
    return 0;
}