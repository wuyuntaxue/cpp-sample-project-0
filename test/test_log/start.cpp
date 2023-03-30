#include "log/log.hpp"

#include <chrono>
#include <thread>

int main() {
    log_init_tmp(); // 初始化spd日志

    // 在初始化日志之后，进程的任意位置可以获取log
    std::shared_ptr<spdlog::logger> _logger = spdlog::get(LOG_TAG);
    _logger->info("hello spdlog");
    for (unsigned int i = 0; i < 100; i++) {
        std::string s1 = "heihei";
        _logger->info("read config file done,{} and {}", 100, s1);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        _logger->warn("[{}:{}]read config file done,{} and {}", __FILENAME__, __LINE__, 102, s1);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        _logger->error("[{}:{}]read config file done,{} and {}", __FILENAME__, __LINE__, 103, s1);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    _logger->warn("[{}:{}]sample project done, goodbye(^_^)\n......", __FILENAME__, __LINE__);
    log_drop(); // 释放日志
}