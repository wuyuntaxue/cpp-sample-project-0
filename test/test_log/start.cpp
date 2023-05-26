#include "log/log.hpp"

#include <sys/prctl.h>

#include <chrono>
#include <thread>

void do_some_log(std::string s1) {
    for (unsigned int i = 0; i < 1000; i++) {
        LOG_INFO("start config file ,{} and {}", i, s1);
        std::this_thread::sleep_for(std::chrono::microseconds(100));

        LOG_WARN("read config file done,{} and {}", i, s1);
        std::this_thread::sleep_for(std::chrono::microseconds(100));

        LOG_ERROR("write config file done,{} and {}", i, s1);
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
}

int main() {
    prctl(PR_SET_NAME, "main");

    LOG_INFO("start test log");

    std::thread th1([] {
        prctl(PR_SET_NAME, "sub th1");
        do_some_log("th1");
    });

    std::thread th2([] {
        prctl(PR_SET_NAME, "sub th2");
        do_some_log("th2");
    });

    do_some_log("main");

    th1.join();
    th2.join();

    LOG_WARN("sample project done, goodbye(^_^)\n......");
    log_drop(); // 释放日志
    return 0;
}