
#include "log/log.hpp"
#include "sqlite3.h"

#include <iostream>
#include <thread>

#define LOG_A(fmt, arg...)

static int callback(__attribute__((unused)) void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

class SqliteRWTest {

public:
    void init() {
        sqlite3_config(SQLITE_CONFIG_SERIALIZED);
        int res = sqlite3_open("user.db", &db);
        if (res != SQLITE_OK) {
            LOG_ERROR("open failed, res: {}", res);
        } else {
            LOG_INFO("open sucess");
        }
    }

    void deinit() {
        sqlite3_close(db);
    }

    void create_table() {
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

    void insert(int count) {
        // const char *sql         = "INSERT INTO COMPANY (ID,AGE,NAME,ADDRESS,SALARY)"
        //                           "VALUES (%d, 19, \"Peter\", \"California\", 20000.00);";
        char        sqlbuf[512] = {0};
        snprintf(sqlbuf, sizeof(sqlbuf), "INSERT INTO COMPANY (ID,AGE,NAME,ADDRESS,SALARY)" \
                                  "VALUES (%d, 19, \"Peter\", \"California\", 20000.00);", count);


        char *errMsg = nullptr;
        int   rc     = sqlite3_exec(db, sqlbuf, callback, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            printf("errmsg: %s\n", errMsg);
            sqlite3_free(errMsg);
        } else {
            printf("insert success\n");
        }
    }

    void get_all() {
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

    void delete_test() {
    // {
    //     const char *sql = "DELETE FROM COMPANY WHERE ID = 2;";

    //     char *errMsg = nullptr;
    //     int   rc     = sqlite3_exec(db, sql, callback, nullptr, &errMsg);

    //     if (rc != SQLITE_OK) {
    //         printf("errmsg: %s\n", errMsg);
    //         sqlite3_free(errMsg);
    //     } else {
    //         printf("delete success\n");
    //     }
    // }
    }


private:
    sqlite3 *db = NULL;
};

int main() {
    LOG_A("abc");

    auto sq = std::make_shared<SqliteRWTest>();
    sq->init();

    sq->create_table();


    std::thread th1([sq]{
        int count = 0;
        while (count++ < 1000) {
            std::this_thread::sleep_for( std::chrono::milliseconds(10));
            sq->insert(count);
        }
        
    });

    std::thread th2([sq]{
        int count = 100000;
        while (count-- > 99000) {
            std::this_thread::sleep_for( std::chrono::milliseconds(9));
            sq->insert(count);
        }
        
    });


    th1.join();
    th2.join();

    sq->get_all();

    sq->deinit();



    return 0;
}