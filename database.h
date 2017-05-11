/**
 * Wrapper for function in sqlite
**/
#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "sqlite3.h"
#include "constant.h"


class SQLite {
    private:
        sqlite3 *db;
        sqlite3_stmt *stmt;
        std::string dbname;
        int rc;
    public:
        SQLite(const std::string&);
        ~SQLite();
        int open_db();
        int exec_db(std::string sql);
        void get_table(std::string sql);
        void get_info(std::string sql);
        void get_phoneNum(std::string sql);
        int get_int(std::string sql);
        double get_double(std::string sql);
        std::string get_str(std::string sql);
        int detect_duplication(DBFlag flag, std::string inName); // detect if there are duplication in product or customer
};

#endif
