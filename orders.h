#ifndef ORDERS_h
#define ORDERS_h 

#include <iostream>
#include <vector>
#include "database.h"
#include "constant.h"

struct orders {
    std::string cusName;
    std::string orderDate;
    std::string requireDate;
    std::string shipDate;
    std::vector<std::string> orderVec;
};

class Orders {
    private:
        SQLite database{dbName};
        orders ordersDetail;
    public:
        Orders();
        ~Orders();
        void main();
        void search(SFlag);
        void update();
        void set_newOrders();
        void set_newOrdersDetail();
        void add_newOrders();
        void add_newOrdersDetail();
        void print_orderStatement(int);
        void search_order_by_name(std::string);
        void search_order_by_date(std::string);
        void get_distinct_date();
        void list_orders();
        void search_orderInfo(int);
        void update_status(int ordersID, int status);
        void set_OrdersDetail();
        void add_OrdersDetail(int orderID);
        void delete_OrdersDetail(int orderID);
        void empty_orderVec(int& quantity, std::string& productCode);
};

#endif /* ifndef ORDERS_h */
