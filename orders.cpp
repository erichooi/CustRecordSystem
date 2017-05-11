#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include "orders.h"
#include "customer.h"
#include "constant.h"
#include "util.h"
#include "interface.h"
#include "product.h"

Orders::Orders() {};

Orders::~Orders() {};

// wrapper for add new order
void Orders::main()
{
    this->set_newOrders();
    this->add_newOrders();
    clrscreen();
    this->set_newOrdersDetail();
    this->add_newOrdersDetail();
    clrscreen();
    this->print_orderStatement(0);
}

// wrapper for search
void Orders::search(SFlag flag)
{
    std::string s_input;
    int orderID;
    std::string sql = "SELECT CUSTOMERNAME FROM CUSTOMER;";
    switch (flag) {
        case SFlag::NAME_FLAG:
            this->database.get_table(sql);
            std::cout << "Enter the NAME: ";
            std::getline(std::cin, s_input);
            clrscreen();
            this->search_order_by_name(s_input);
            break;
        case SFlag::DATE_FLAG:
            this->get_distinct_date();
            std::cout << "Enter the DATE: ";
            std::getline(std::cin, s_input); clrscreen();
            this->search_order_by_date(s_input);
            break;
        case SFlag::ORDERID_FLAG:
            this->list_orders();
            break;
    }
    std::cout << "Enter the ORDERID: ";
    std::cin >> orderID;
    std::cin.ignore();
    clrscreen();
    this->search_orderInfo(orderID);
}

// wrapper for update
void Orders::update()
{
    Interface orders_interface;
    Product product;
    int ordersID;
    this->list_orders();
    std::cout << "Enter the order's ID: ";
    std::cin >> ordersID;
    std::cin.ignore();
    clrscreen();
    orders_interface.order_update_page(ordersID);
    clrscreen();
    switch (orders_interface.get_choice()) {
        case 'a':
            orders_interface.order_update_status_page();
            if (orders_interface.get_choice() == 'a') {
                this->update_status(ordersID, 1);
            } else if (orders_interface.get_choice() == 'b') {
                this->update_status(ordersID, 2);
            }
            this->print_orderStatement(ordersID);
            break;
        case 'b':
            std::cout << "Add Product\n\n";
            product.list_productID();
            std::cout << "\n";
            this->set_OrdersDetail();
            this->add_OrdersDetail(ordersID);
            this->print_orderStatement(ordersID);
            break;
        case 'c':
            std::cout << "Delete Product\n\n";
            this->delete_OrdersDetail(ordersID);
            this->print_orderStatement(ordersID);
            break;
    }
}

void Orders::set_newOrders()
{
    Customer cust;
    DBFlag flag = DBFlag::CUS_FLAG;
    std::string sql;
    int duplicate;
    bool endFlag = false;
    std::cout << std::left;
    do {
        std::cout << "\n";
        std::cout << "-------------------------\n";
        std::cout << "| New Order Information |\n";
        std::cout << "-------------------------\n\n";
        cust.list_cusName();
        std::cout << std::setw(w30) << "Customer Name" << ": ";
        std::getline(std::cin, this->ordersDetail.cusName);

        duplicate = this->database.detect_duplication(flag, this->ordersDetail.cusName);
        if (duplicate == 1) {
            endFlag = true;
        } else {
            show_dialog("No such NAME in database!");
            clrscreen();
        }
    } while (endFlag == false);
    std::cout << std::setw(w30) << "Order Date (default = today)" << ": ";
    std::getline(std::cin, this->ordersDetail.orderDate);
    if (this->ordersDetail.orderDate.empty()) {
        this->ordersDetail.orderDate = "NULL";
    }
    std::cout << std::setw(w30) << "Require Date (yyyy-mm-dd)" << ": ";
    std::getline(std::cin, this->ordersDetail.requireDate);
}

void Orders::set_newOrdersDetail()
{
    Product product;
    std::cout << "\n";
    std::cout << "-------------------------\n";
    std::cout << "| New Order Information |\n";
    std::cout << "-------------------------\n\n";
    product.list_productID();
    std::cout << "\n";
    this->set_OrdersDetail();
}

void Orders::add_newOrders()
{
    std::string sql;
    sql = "SELECT CUSTOMERID FROM CUSTOMER WHERE CUSTOMERNAME=\"" 
          + this->ordersDetail.cusName + "\";";
    int cusID = this->database.get_int(sql);
    if (this->ordersDetail.orderDate == "NULL") {
        sql = "INSERT INTO ORDERS(CUSTOMERID, REQUIREDATE) VALUES(" 
              + std::to_string(cusID) + ",\"" + this->ordersDetail.requireDate 
              + "\");";
    } else {
        sql = "INSERT INTO ORDERS(CUSTOMERID, ORDERDATE, REQUIREDATE) VALUES(" 
              + std::to_string(cusID) + ",\"" + this->ordersDetail.orderDate 
              + "\",\"" + this->ordersDetail.requireDate + "\");";
    }
    this->database.exec_db(sql);
}

void Orders::add_newOrdersDetail()
{
    std::string sql;
    int orderID;
    sql = "SELECT LAST_INSERT_ROWID();";
    orderID = this->database.get_int(sql);
    this->add_OrdersDetail(orderID);
}

void Orders::print_orderStatement(int orderID)
{
    std::string sql, customerName, orderDate, requireDate, status;
    int cond;
    double sum;
    if (orderID == 0) {
        sql = "SELECT MAX(ORDERID) FROM ORDERS;";
        orderID = this->database.get_int(sql);
    } 
    std::cout << std::fixed << std::setprecision(2) << std::left;
    std::cout << "\n";
    std::cout << "Order Statement\n\n";
    std::cout << std::setw(w20) << "Order ID" << ": " << orderID << std::endl;
    sql = "SELECT CUSTOMERNAME FROM CUSTOMER JOIN ORDERS WHERE CUSTOMER.CUSTOMERID" 
          "=ORDERS.CUSTOMERID AND ORDERID=" + std::to_string(orderID) + ";";
    customerName = this->database.get_str(sql);
    std::cout << std::setw(w20) << "Customer Name" << ": " << customerName << std::endl;
    sql = "SELECT ORDERDATE FROM ORDERS WHERE ORDERID=" + std::to_string(orderID) + ";";
    orderDate = this->database.get_str(sql);
    std::cout << std::setw(w20) << "Order Date" << ": " << orderDate << std::endl;
    sql = "SELECT REQUIREDATE FROM ORDERS WHERE ORDERID=" + std::to_string(orderID) + ";";
    requireDate = this->database.get_str(sql);
    std::cout << std::setw(w20) << "Require Date" << ": " << requireDate << std::endl; std::cout << "\n";
    sql = "SELECT PRODUCT.PRODUCTCODE AS 'CODE', PRODUCT.PRODUCTNAME AS 'PRODUCT NAME'"
          ", ORDERDETAIL.QUANTITY AS 'QUANTITY', PRODUCT.PRICE AS 'PRICE (RM)'"
          ", ORDERDETAIL.QUANTITY * PRODUCT.PRICE AS 'TOTAL (RM)' FROM ORDERDETAIL JOIN PRODUCT ON"
          " ORDERDETAIL.PRODUCTID=PRODUCT.PRODUCTID WHERE ORDERDETAIL.ORDERID=" 
          + std::to_string(orderID) + ";";
    this->database.get_table(sql);
    sql = "SELECT SUM(ORDERDETAIL.QUANTITY * PRODUCT.PRICE) FROM ORDERDETAIL JOIN PRODUCT"
          " ON ORDERDETAIL.PRODUCTID=PRODUCT.PRODUCTID WHERE ORDERDETAIL.ORDERID=" 
          + std::to_string(orderID) + ";";
    sum = this->database.get_double(sql);
    std::cout << "|" << std::setw(83) << "Sum" << "|" << std::setw(w20) << sum << "|" << std::endl;
    std::cout << std::setw(105) << std::setfill('-') << " " << std::setfill(' ') << " " << std::endl;
    std::cout << "\n";
    std::cout << std::setw(w20) << "Status" << ": ";
    sql = "SELECT STATUS FROM ORDERS WHERE ORDERID=" + std::to_string(orderID);
    cond = this->database.get_int(sql);
    if (cond == 0) {
        status = "Incomplete";
    } else if (cond == 1) {
        status = "Completed";
    } else {
        status = "Cancelled";
    }
    std::cout << status << std::endl;
}

void Orders::search_order_by_name(std::string name)
{
    std::cout << "\n";
    std::cout << "-----------------\n";
    std::cout << "| Order by NAME |\n";
    std::cout << "-----------------\n\n";
    std::string sql;
    sql = "SELECT ORDERS.ORDERID, CUSTOMER.CUSTOMERNAME, ORDERS.ORDERDATE"
          " FROM ORDERS JOIN CUSTOMER ON ORDERS.CUSTOMERID=CUSTOMER.CUSTOMERID"
          " WHERE CUSTOMER.CUSTOMERNAME=\"" + name + "\";";
    this->database.get_table(sql);
}

void Orders::search_order_by_date(std::string date)
{
    std::cout << "\n";
    std::cout << "-----------------\n";
    std::cout << "| Order by DATE |\n";
    std::cout << "-----------------\n\n";
    std::string sql;
    sql = "SELECT ORDERS.ORDERID, CUSTOMER.CUSTOMERNAME, ORDERS.ORDERDATE"
          " FROM ORDERS JOIN CUSTOMER ON ORDERS.CUSTOMERID=CUSTOMER.CUSTOMERID"
          " WHERE ORDERS.ORDERDATE=\"" + date + "\";";
    this->database.get_table(sql);
}


void Orders::get_distinct_date()
{
    std::string sql;
    sql = "SELECT DISTINCT ORDERS.ORDERDATE FROM ORDERS";
    this->database.get_table(sql);
}

void Orders::list_orders()
{
    std::string sql;
    sql = "SELECT ORDERS.ORDERID, CUSTOMER.CUSTOMERNAME, ORDERS.ORDERDATE"
          " FROM ORDERS JOIN CUSTOMER ON ORDERS.CUSTOMERID=CUSTOMER.CUSTOMERID;";
    this->database.get_table(sql);
}

void Orders::search_orderInfo(int orderID)
{
    std::cout << "\n";
    std::cout << "----------------\n";
    std::cout << "| Order Detail |\n";
    std::cout << "----------------\n\n";
    this->print_orderStatement(orderID);
}
 
void Orders::update_status(int ordersID, int status)
{
    std::string sql;
    sql = "UPDATE ORDERS SET STATUS=" + std::to_string(status) 
          + " WHERE ORDERID=" + std::to_string(ordersID) + ";";
    this->database.exec_db(sql);
}

void Orders::set_OrdersDetail()
{
    std::string orderInfo;
    int pass;
    std::cout << "Enter the Product Code with Quantity" << std::endl;
    std::cout << "Example: CK,9;FC,10" << std::endl;
    do {
        std::cout << ">> ";
        std::getline(std::cin, orderInfo);
        pass = tokenize(orderInfo, this->ordersDetail.orderVec, ",;");
    } while (pass = 0);
}

void Orders::add_OrdersDetail(int orderID)
{
    std::string sql, productCode;
    int quantity, productID, orderDetailID, temp;
    while (!this->ordersDetail.orderVec.empty()) {
        this->empty_orderVec(quantity, productCode);
        sql = "SELECT PRODUCTID FROM PRODUCT WHERE PRODUCTCODE=\"" + productCode + "\";";
        productID = this->database.get_int(sql);
        if (productID == 0) {
            std::cout << productCode << " is not in the database!" << std::endl;
            continue;
        }
        // check if the data repeated. If repeated, add with the current quantity
        sql = "SELECT ORDERDETAILID FROM ORDERDETAIL WHERE ORDERID=" + std::to_string(orderID)
              + " AND PRODUCTID=" + std::to_string(productID) + ";";
        if (this->database.get_int(sql)) {
            orderDetailID = this->database.get_int(sql);
            sql = "SELECT QUANTITY FROM ORDERDETAIL WHERE ORDERDETAILID=" 
                  + std::to_string(orderDetailID) + ";";
            temp = this->database.get_int(sql);
            quantity = quantity + temp;
            sql = "UPDATE ORDERDETAIL SET QUANTITY=" + std::to_string(quantity) 
                  + " WHERE ORDERDETAILID=" + std::to_string(orderDetailID) + ";";
            this->database.exec_db(sql);
        } else {
            sql = "INSERT INTO ORDERDETAIL(ORDERID, PRODUCTID, QUANTITY) VALUES(" 
                  + std::to_string(orderID) + "," + std::to_string(productID) 
                  + "," + std::to_string(quantity) + ");";
            this->database.exec_db(sql);
        }
    }
}

void Orders::delete_OrdersDetail(int orderID)
{
    std::string sql, productCode;
    int quantity, productID, orderDetailID, temp;
    sql = "SELECT PRODUCT.PRODUCTCODE AS 'CODE', PRODUCT.PRODUCTNAME AS 'PRODUCT NAME',"
          " ORDERDETAIL.QUANTITY AS 'QUANTITY' FROM ORDERDETAIL JOIN PRODUCT ON"
          " ORDERDETAIL.PRODUCTID=PRODUCT.PRODUCTID WHERE ORDERDETAIL.ORDERID=" 
          + std::to_string(orderID) + ";";
    this->database.get_table(sql);
    std::cout << "\n";
    this->set_OrdersDetail();
    while (!this->ordersDetail.orderVec.empty()) {
        this->empty_orderVec(quantity, productCode);
        sql = "SELECT PRODUCTID FROM PRODUCT WHERE PRODUCTCODE=\"" + productCode + "\";";
        productID = this->database.get_int(sql);
        if (productID == 0) {
            show_dialog(productCode + " is not in the database!");
            continue;
        }
        sql = "SELECT ORDERDETAILID FROM ORDERDETAIL WHERE ORDERID=" + std::to_string(orderID)
              + " AND PRODUCTID=" + std::to_string(productID) + ";";
        if (this->database.get_int(sql)) {
            orderDetailID = this->database.get_int(sql);
            sql = "SELECT QUANTITY FROM ORDERDETAIL WHERE ORDERDETAILID=" 
                  + std::to_string(orderDetailID) + ";";
            temp = this->database.get_int(sql);
            quantity = temp - quantity;
            if (quantity <= 0) {
                sql = "DELETE FROM ORDERDETAIL WHERE ORDERDETAILID=" 
                      + std::to_string(orderDetailID) + ";";
            } else {
                sql = "UPDATE ORDERDETAIL SET QUANTITY=" + std::to_string(quantity) 
                      + " WHERE ORDERDETAILID=" + std::to_string(orderDetailID) + ";";
            }
            this->database.exec_db(sql);
        } else {
            show_dialog("No such order!");
            continue;
        }
    }
}

void Orders::empty_orderVec(int& quantity, std::string& productCode) 
{
    quantity = std::atoi(this->ordersDetail.orderVec.back().c_str());
    this->ordersDetail.orderVec.pop_back();
    productCode = std::move(this->ordersDetail.orderVec.back());
    this->ordersDetail.orderVec.pop_back();
}
