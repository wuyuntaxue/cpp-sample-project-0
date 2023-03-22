#include "base64/base64.hpp"
#include "config/config.hpp"
#include "log/log.hpp"

#include <iostream>

// base64演示
void base64_test() {
    std::shared_ptr<spdlog::logger> _logger = spdlog::get(LOG_TAG);

    const char *name = "Where there's pain, there's life.";
    // base64编码，传入数组和数据长度，返回string类型的base64字符串
    std::string baseStr = base64_encode(name, strlen(name));

    _logger->warn("baseStr: {}", baseStr);

    // base64解码，传入base64字符串，返回解码后的string
    std::string resultStr = base64_decode(baseStr);
    _logger->warn("resultStr: {}", resultStr);
}

int main() {
    std::cout << "taxue sample start" << std::endl;
    log_init(); // 初始化spd日志

    // 在初始化日志之后，进程的任意位置可以获取log
    std::shared_ptr<spdlog::logger> _logger = spdlog::get(LOG_TAG);
    _logger->info("hello spdlog");

    // 读写yaml配置文件
    std::shared_ptr<configType> pConfig = std::make_shared<configType>(DEFAULT_CONFIG_FILENAME);
    pConfig->read_config_file();
    pConfig->print_config();

    pConfig->data.name += "a";
    pConfig->data.age += 1;
    pConfig->data.grade += 1.1;
    pConfig->data.isHuman = !pConfig->data.isHuman;
    pConfig->data.numbers.push_back(100);

    pConfig->save_config_file();
    /////////////////

    // 日志演示
    std::string s1 = "heihei";
    _logger->info("read config file done,{} and {}", 100, s1);
    _logger->warn("[{}:{}]read config file done,{} and {}", __FILENAME__, __LINE__, 100, s1);
    _logger->error("[{}:{}]read config file done,{} and {}", __FILENAME__, __LINE__, 100, s1);
    ////////////////

    base64_test();

    _logger->warn("[{}:{}]sample project done, goodbye(^_^)\n......", __FILENAME__, __LINE__);
    log_drop(); // 释放日志
    return 0;
}