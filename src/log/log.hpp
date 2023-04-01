#ifndef __LOGGER_HPP
#define __LOGGER_HPP

#include "spdlog/spdlog.h"

#include <string.h>

std::shared_ptr<spdlog::logger> log_init(void);
void log_drop(void);


std::shared_ptr<spdlog::logger> __get_log(void);

// 避免修改__FILE__宏引起的冲突，使用宏定义，日志中文件名使用相对路径
#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : __FILE__)

#define LOG_INFO(fmt, ...)    \
__get_log()->info(" " fmt"", ##__VA_ARGS__)

#define LOG_WARN(fmt, ...)    \
__get_log()->warn("[{}:{}] " fmt"", __FILENAME__, __LINE__, ##__VA_ARGS__)

#define LOG_ERROR(fmt, ...)    \
__get_log()->error("[{}:{}] " fmt"", __FILENAME__, __LINE__, ##__VA_ARGS__)


#endif