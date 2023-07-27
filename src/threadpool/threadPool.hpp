/**
 * @file threadPool.hpp
 * @author your name (you@domain.com)
 * @brief 线程池
 * @version 0.1
 * @date 2023-07-17
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include "log/log.hpp"

#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

/// TODO ： 线程数量的调整，不指定时自动增减？

namespace TOOL {
    class ThreadPool {
    public:
        ThreadPool();
        ~ThreadPool();
        ThreadPool(const ThreadPool &) = delete;

        void start(int maxThreadCounts, std::string tName = "");
        void stop();

        template <typename F, typename... Args>
        auto add_task(F &&f, Args &&...args) -> std::future<decltype(f(args...))>;

    private:
        std::mutex                        _mtlck;
        std::condition_variable           _cond;
        std::mutex                        _thoptlck;
        std::vector<std::thread>          _workth;
        std::queue<std::function<void()>> _task_queue;

        bool _running;
    };

    template <typename F, typename... Args>
    auto ThreadPool::add_task(F &&f, Args &&...args) -> std::future<decltype(f(args...))> {
        // 用bind绑定函数,将函数适配成无参数列表的函数对象(返回值类型不变)
        auto func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

        // 用packaged_task将函数封装成可以异步获取调用结果的对象(用于获取返回值)
        auto task = std::make_shared<std::packaged_task<decltype(f(args...))()>>(std::move(func));

        std::unique_lock<std::mutex> lck(_mtlck);

        // 将task的调用写在lambda表达式内,传入工作队列(这个lambda是无参数\无返回值的function类型)
        _task_queue.emplace([task] { (*task)(); });

        // 通知空闲的线程
        _cond.notify_one();

        // 返回future(函数的异步执行结果)
        return task->get_future();
    }

    ThreadPool::ThreadPool()
        : _running(false) {}

    ThreadPool::~ThreadPool() {
        stop();
    }

    void ThreadPool::start(int maxThreadCounts, std::string tName) {
        if (maxThreadCounts <= 0) {
            LOG_ERROR("max thread count invalid: {}", maxThreadCounts);
            return;
        }
        if (_running) {
            LOG_ERROR("already running");
            return;
        }
        std::unique_lock<std::mutex> thlck(_thoptlck);
        _running = true;

        for (int i = 0; i < maxThreadCounts && _running; i++) {

            _workth.emplace_back(std::thread([this, i, tName]() {
                LOG_INFO("start thread[{}-{}]", i, tName);
                for (; this->_running;) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lck(this->_mtlck);
                        this->_cond.wait(lck,
                                         [this] { return !this->_running || !this->_task_queue.empty(); });
                        // or
                        // if (this->_task_queue.empty() && this->_running) {
                        //     this->_cond.wait(lck);
                        // }

                        if (!this->_task_queue.empty()) {
                            task = std::move(this->_task_queue.front());
                            this->_task_queue.pop();
                        } else {
                            continue;
                        }
                    }
                    if (this->_running) {
                        task();
                    }
                }
                LOG_INFO("thread[{}-{}] exit", i, tName);
            }));
        }
    }

    void ThreadPool::stop() {
        {
            std::unique_lock<std::mutex> lck(_mtlck);
            _running = false;
            for (; !_task_queue.empty();) {
                _task_queue.pop();
            }
        }

        std::unique_lock<std::mutex> thlck(_thoptlck);
        _cond.notify_all();
        for (auto &i : _workth) {
            i.join();
        }
        _workth.clear();
    }
} // namespace TOOL