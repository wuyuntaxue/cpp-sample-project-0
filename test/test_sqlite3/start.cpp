
#include "log/log.hpp"
#include "sqlite3.h"

#include <iostream>


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    sqlite3 *db  = NULL;
    int      res = sqlite3_open("user.db", &db);
    if (res != SQLITE_OK) {
        LOG_ERROR("open failed, res: {}", res);
    } else {
        LOG_INFO("open sucess");
    }

    /// 创建表
    {
        const char *sql = "CREATE TABLE COMPANY("
                          "ID INT PRIMARY KEY     NOT NULL,"
                          "NAME           TEXT    NOT NULL,"
                          "AGE            INT     NOT NULL,"
                          "ADDRESS        CHAR(50),"
                          "SALARY         REAL );";

        char *errMsg = nullptr;
        int   rc     = sqlite3_exec(db, sql, callback, nullptr, &errMsg);

        if (rc != SQLITE_OK) {
            printf("errmsg: %s\n", errMsg);
            sqlite3_free(errMsg);
        } else {
            printf("create table success\n");
        }
    }

    /// 向表中插入一条记录
    {
        const char *sql = "INSERT INTO COMPANY (ID,AGE,NAME,ADDRESS,SALARY)"
                          "VALUES (2, 19, \"Peter\", \"California\", 20000.00);";

        char *errMsg = nullptr;
        int   rc     = sqlite3_exec(db, sql, callback, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            printf("errmsg: %s\n", errMsg);
            sqlite3_free(errMsg);
        } else {
            printf("insert success\n");
        }
    }

    /// 从表中获取所有字段
    {
        const char *sql = "SELECT * FROM COMPANY;";

        char *errMsg = nullptr;
        int   rc     = sqlite3_exec(db, sql, callback, nullptr, &errMsg);

        if (rc != SQLITE_OK) {
            printf("errmsg: %s\n", errMsg);
            sqlite3_free(errMsg);
        } else {
            printf("select success\n");
        }
    }

    {
        const char *sql = "DELETE FROM COMPANY WHERE ID = 2;";

        char *errMsg = nullptr;
        int   rc     = sqlite3_exec(db, sql, callback, nullptr, &errMsg);

        if (rc != SQLITE_OK) {
            printf("errmsg: %s\n", errMsg);
            sqlite3_free(errMsg);
        } else {
            printf("delete success\n");
        }
    }


    sqlite3_close(db);
    return 0;
}