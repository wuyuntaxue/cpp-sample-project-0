#include "log/log.hpp"
#include "threadpool/threadPool.hpp"

#include <semaphore.h>
#include <csignal>
#include <string>


void test_func(std::string name) {
    LOG_WARN("dotask testFunc, {}", name);
    std::this_thread::sleep_for(std::chrono::seconds(1));
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
    LOG_INFO("start thread pool test ... ...");

    ThreadPool pool;
    pool.start(3, "lamba");

    for (int i = 0; i < 20; i++) {
        pool.add_task([](int i) {
            LOG_WARN("dotask func {}", i);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }, i);
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));

    pool.stop();

    pool.start(2, "func");

    for (int i = 0; i < 20; i++) {
        pool.add_task(test_func, "test" + std::to_string(i));
    }

    /// 阻塞主函数，等待退出信号
    wait_exit_signal();

    pool.stop();

    LOG_WARN("thread pool test done");
    log_drop(); // 释放日志
    return 0;
}