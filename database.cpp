#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iomanip>
#include "sqlite3.h"
#include "database.h"
#include "constant.h"


SQLite::SQLite(const std::string& dbname) 
{
    this->dbname = dbname;
    open_db();
}

SQLite::~SQLite() 
{
    sqlite3_close(db);
}

int SQLite::open_db()
{
    rc = sqlite3_open(this->dbname.c_str(), &db);
    if (rc) {
        std::cout << "Can't open database: " << sqlite3_errmsg(db);
        return 0;
    }
}

int SQLite::exec_db(std::string sql) 
{
    sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, NULL);
    rc = sqlite3_step(stmt);
    rc = sqlite3_finalize(stmt);
    if (rc) {
        std::cout << "Failed to execute: " << sqlite3_errmsg(db);
        return 0;
    }
}

void SQLite::get_table(std::string sql)
{
    char** result;
    char* zErrMsg;
    int nrows, ncols, i, j;
    rc = sqlite3_get_table(db, sql.c_str(), &result, &nrows, &ncols, &zErrMsg);
    std::cout << std::left;
    for (i = 0; i < nrows + 1; i++) {
        if (i == 0) {
            std::cout << std::setw(ncols * (w20 + 1)) << std::setfill('-') << " " << " " << std::endl;
            std::cout << std::setfill(' ');
        }
        std::cout << "|";
        for(j = 0; j < ncols; j++) {
            std::cout << std::setw(w20) << result[i * ncols + j] << "|";
        }
        std::cout << "\n";
        if (i == 0 || i == nrows) {
            std::cout << std::setw(ncols * (w20 + 1)) << std::setfill('-') << " " << " " << std::endl;
            std::cout << std::setfill(' ');
        }
    }
    sqlite3_free_table(result);
}

void SQLite::get_info(std::string sql)
{
    int i;
    std::string name, type;
    sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, NULL);
    int ncols = sqlite3_column_count(stmt);
    rc = sqlite3_step(stmt);
    for (i = 0; i < ncols; i++) {
        name = sqlite3_column_name(stmt, i);
        type = sqlite3_column_decltype(stmt, i);
        std::cout << std::setw(w20) << name << ": ";
        if (type == "TEXT") {
            std::string text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            std::cout << text << std::endl;
        } else {
            int text = sqlite3_column_int(stmt, i);
            std::cout << text << std::endl;
        }
    }
    sqlite3_finalize(stmt);
}

void SQLite::get_phoneNum(std::string sql)
{
    int i, ncols;
    std::string name, text;
    sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, NULL);
    rc = sqlite3_step(stmt);
    ncols = sqlite3_column_count(stmt);
    while (rc == SQLITE_ROW) {
        for (i = 0; i < ncols; i++) {
            name = sqlite3_column_name(stmt, i);
            text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            std::cout << std::setw(w20) << name << ": ";
            std::cout << text << std::endl;
        }
        rc = sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
}

int SQLite::get_int(std::string sql)
{
    sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, NULL);
    rc = sqlite3_step(stmt);
    int result;
    if (sqlite3_column_int(stmt, 0)) {
        result = sqlite3_column_int(stmt, 0);
    } else {
        result = 0;
    }
    rc = sqlite3_finalize(stmt);
    return result;
}

double SQLite::get_double(std::string sql)
{
    sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, NULL);
    rc = sqlite3_step(stmt);
    double result;
    if (sqlite3_column_double(stmt, 0)) {
        result = sqlite3_column_double(stmt, 0);
    } else {
        result = 0.0;
    }
    rc = sqlite3_finalize(stmt);
    return result;
}

std::string SQLite::get_str(std::string sql)
{
    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, NULL);
    rc = sqlite3_step(stmt);
    std::string result;
    if (sqlite3_column_text(stmt, 0)) {
        result = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    } else {
        result = "NULL";
    }
    rc = sqlite3_finalize(stmt);
    return result;
}

int SQLite::detect_duplication(DBFlag flag, std::string inName)
// DBFlag(database flag) is in constant.h
{
    SQLite database{dbName};
    int duplicate_flag = 0;
    std::string sql, dbName;
    switch (flag) {
        case DBFlag::CUS_FLAG:
            sql = "SELECT CUSTOMERNAME FROM CUSTOMER WHERE CUSTOMERNAME=\"" + inName + "\";";
            break;
        case DBFlag::PRO_FLAG:
            sql = "SELECT PRODUCTNAME FROM PRODUCT WHERE PRODUCTNAME=\"" + inName + "\";";
            break;
    }
    dbName = database.get_str(sql);
    if (dbName.compare(inName) == 0) {
        duplicate_flag = 1;
    }
    return duplicate_flag;
}
