#include "log/log.hpp"
#include "uuid/uuid.h"

#include <chrono>
#include <string>
#include <thread>


std::string create_uuid() {
    uuid_t uuid;
    uuid_generate(uuid);

    // len 8 + 4 + 4 + 4 + 12
    // ex. "7ee76d9c-e4c0-4181-90ad-c53dbedb63ba" + "\0"
    char uuid_str[37];
    uuid_unparse_lower(uuid, uuid_str);

    std::string idStr(uuid_str);
    return idStr;
}

int main() {
    LOG_INFO("start test");

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < 100; i++) {
        LOG_WARN("uuid[{}]: {}", i, create_uuid());
    }

    /// 计算执行时间
    std::chrono::duration<double, std::milli> diff = std::chrono::steady_clock::now() - start;
    LOG_WARN("cost time: {}ms", diff.count());

    return 0;
}