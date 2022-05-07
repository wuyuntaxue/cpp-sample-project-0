#ifndef __LOGGER_HPP
#define __LOGGER_HPP

#include "spdlog/spdlog.h"
#include <string.h>

void log_init(void);
void log_drop(void);

//避免修改__FILE__宏引起的冲突，使用宏定义，日志中文件名使用相对路径
#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)

//日志标识符，初始化以后在进程内依此标识符使用log
#define LOG_TAG "taxue"


#endif