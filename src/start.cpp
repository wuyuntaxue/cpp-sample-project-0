#include "config/config.hpp"
#include "log/log.hpp"
#include "threadpool/threadPool.hpp"

#include <semaphore.h>

#include <csignal>
#include <iostream>
#include <memory>
#include <string>


void config_file_test() {
    // 读写yaml配置文件
    configType::Instance().read_config_file("./config.yaml");
    configType::Instance().print_config();

    configType::Instance().data.name += "a";
    configType::Instance().data.age += 1;
    configType::Instance().data.grade += 1.1;
    configType::Instance().data.isHuman = !configType::Instance().data.isHuman;
    configType::Instance().data.numbers.push_back(100);

    configType::Instance().save_config_file();
}


static void wait_exit_signal() {
    static sem_t sem;
    sem_init(&sem, 0, 0);
    signal(SIGINT, [](int) {
        LOG_WARN("recv exit signal");
        sem_post(&sem);
    });

    sem_wait(&sem);
    sem_destroy(&sem);
}

int main() {
    std::cout << "taxue sample start" << std::endl;
    LOG_INFO("start run ... ...");

    /// 阻塞主函数，等待退出信号
    wait_exit_signal();

    LOG_WARN("sample project done, goodbye(^_^)\n......");
    log_drop(); // 释放日志
    return 0;
}