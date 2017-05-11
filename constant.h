/** 
 * Store constant variable
**/
#ifndef CONSTANT_H
#define CONSTANT_H 

#include <iostream>

enum class DBFlag {
    CUS_FLAG,
    PRO_FLAG,
};

// search flag for orders
enum class SFlag {
    NAME_FLAG,
    DATE_FLAG,
    ORDERID_FLAG,
};

const std::string dbName = "customer.db";
const int w20 = 20;
const int w30 = 30;
const int w40 = 40;

#endif /* ifndef CONSTANT_H */
