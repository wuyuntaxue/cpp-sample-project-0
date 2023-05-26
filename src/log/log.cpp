#include "log.hpp"

#include "spdlog/async.h"
#include "spdlog/sinks/rotating_file_sink.h" // support for rotating file logging
#include "spdlog/sinks/sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include <memory>

// 日志文件的路径
#define LOG_FILE_PATH "taxue.log"

// 日志标识符，初始化以后在进程内依此标识符使用log
#define LOG_TAG "taxue"

#if 0
void log_init() {
    try {
        // create a file rotating logger with 50mb size max and 3 rotated files
        auto logger = spdlog::rotating_logger_mt<spdlog::async_factory>(LOG_TAG, LOG_FILE_PATH, 1024 * 1024 * 50, 3);
        // 设置格式：[日期 时间] [日志等级缩写] 正文
        logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e]%^[%L] %v%$");
        // 等级比warn高时，立即刷新，其他等级spdlog在它认为合适的时间刷新
        logger->flush_on(spdlog::level::warn);
    }
    catch (const spdlog::spdlog_ex &ex) {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }
}

#endif

static std::shared_ptr<spdlog::logger> log_init() {
    // 一个日志器使用多个SINK，标准控制台输出和日志文件
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    sinks.push_back(
        std::make_shared<spdlog::sinks::rotating_file_sink_mt>(LOG_FILE_PATH, 1024 * 1024 * 50, 3));
    auto _logger = std::make_shared<spdlog::logger>(LOG_TAG, begin(sinks), end(sinks));
    // 设置格式：[日期 时间] [日志等级缩写] 正文
    _logger->set_pattern("%Y-%m-%d %H:%M:%S.%e%^[%L]%v%$");
    // 等级比warn高时，立即刷新，其他等级spdlog在它认为合适的时间刷新
    _logger->flush_on(spdlog::level::warn);

    spdlog::register_logger(_logger);
    return _logger;
}

void log_drop() {
    spdlog::drop(LOG_TAG);
    spdlog::shutdown();
}

std::shared_ptr<spdlog::logger> &__get_log() {
    static std::shared_ptr<spdlog::logger> _logger = spdlog::get(LOG_TAG);
    if (_logger == nullptr) {
        _logger = log_init();
        if (_logger == nullptr) {
            abort();
        }
    }
    return _logger;
}


// 三个等级的示例
//  _logger->info("info message");
//  _logger->warn("[{}:{}]waring message ", __FILENAME__, __LINE__);
//  _logger->error("[{}:{}]error message", __FILENAME__, __LINE__);