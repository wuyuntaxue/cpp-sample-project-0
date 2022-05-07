#include "log.hpp"
#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h" // support for rotating file logging
#include <memory>

//日志文件的路径
#define LOG_FILE_PATH "taxue.log"

void log_init(){
    try {
        // create a file rotating logger with 50mb size max and 3 rotated files
        auto logger = spdlog::rotating_logger_mt( LOG_TAG, LOG_FILE_PATH, 1024 * 1024 * 50, 3);
        //设置格式：[日期 时间] [日志等级缩写] 正文
        logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e]%^[%L] %v%$");
        //等级比warn高时，立即刷新，其他等级spdlog在它认为合适的时间刷新
        logger->flush_on(spdlog::level::warn);

    }catch (const spdlog::spdlog_ex& ex){
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }
}

void log_drop(){
    spdlog::drop(LOG_TAG);
    spdlog::shutdown();
}

//三个等级的示例
// _logger->info("info message");
// _logger->warn("[{}:{}]waring message ", __FILENAME__, __LINE__);
// _logger->error("[{}:{}]error message", __FILENAME__, __LINE__);