#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include "database.h"
#include "constant.h"

struct customerAddress {
    std::string address1;
    std::string address2;
    std::string city;
    std::string state;
    int postalCode;
    std::string country;
};

struct customerDetail {
    std::string name;
    int phone;
    customerAddress address;
};

// handle all the function related to customer
class Customer {
    private:
        SQLite database{dbName};
        customerDetail cusDetail;
        customerAddress upAddress;
        int upPhone;
    public:
        Customer();
        ~Customer();
        void main();
        void search();
        void update();
        std::string get_customerName(int customerID);
        void set_cusDetail();
        void add_newCustomer();
        void list_cusName();
        void search_cusInfo(int customerID);
        void add_phone(int customerID);
        void delete_phone(int customerID);
        void update_address(int customerID);
};

#endif
