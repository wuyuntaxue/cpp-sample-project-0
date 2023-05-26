
#include "log/log.hpp"
#include <iostream>
#include "sqlite3.h"

int main() {
    sqlite3 *db=NULL;
    int res = sqlite3_open("user.db", &db);
    if (res != SQLITE_OK) {
        LOG_ERROR("open failed, res: {}", res);
    } else {
        LOG_INFO("open sucess");
    }

    sqlite3_close(db);
    return 0;
}