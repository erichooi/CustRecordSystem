#include <iostream>
#include <iomanip>
#include <string>
#include "customer.h"
#include "constant.h"
#include "database.h"
#include "util.h"
#include "interface.h"


Customer::Customer() {};

Customer::~Customer() {};

// wrapper for add new customer
void Customer::main()
{
    this->set_cusDetail();
    this->add_newCustomer();
}

// wrapper for search customer
void Customer::search()
{
    int customerID;
    this->list_cusName();
    std::cout << "Enter the customer's ID: ";
    std::cin >> customerID;
    std::cin.ignore();
    clrscreen();
    this->search_cusInfo(customerID);
}

// wrapper for update customer
void Customer::update()
{
    Interface customer_interface;
    int customerID;
    std::string customerName;
    this->list_cusName();
    std::cout << "Enter the customer's ID: ";
    std::cin >> customerID;
    std::cin.ignore();
    customerName = this->get_customerName(customerID);
    clrscreen();
    customer_interface.customer_update_page(customerName);
    clrscreen();
    switch (customer_interface.get_choice()) {
        case 'a':
            customer_interface.customer_update_phone_page();
            clrscreen();
            if (customer_interface.get_choice() == 'a') {
                this->add_phone(customerID);
            } else if (customer_interface.get_choice() == 'b') {
                this->delete_phone(customerID);
            } 
            break;
        case 'b':
            this->update_address(customerID);
            break;
    }
}

std::string Customer::get_customerName(int customerID)
{
    std::string sql, customerName;
    sql = "SELECT CUSTOMERNAME FROM CUSTOMER WHERE CUSTOMERID=" 
          + std::to_string(customerID) + ";";
    customerName = this->database.get_str(sql);
    return customerName;
}

void Customer::set_cusDetail() 
{
    DBFlag flag = DBFlag::CUS_FLAG;
    int duplicate;
    bool endFlag = false;
    std::cout << std::left;
    do {
        std::cout << "\n";
        std::cout << "----------------------------\n";
        std::cout << "| New Customer Information |\n";
        std::cout << "----------------------------\n\n";
        std::cout << std::setw(w20) << "Name" << ": ";
        std::getline(std::cin, this->cusDetail.name);

        duplicate = this->database.detect_duplication(flag, this->cusDetail.name);
        if (duplicate == 1) {
            show_dialog("DUPLICATE data detected!");
			clrscreen();
        } else {
            endFlag = true;
        }
    } while (endFlag == false);
    std::cout << std::setw(w20) << "Phone" << ": ";
    std::cin >> this->cusDetail.phone;
    std::cin.ignore();
    std::cout << std::setw(w20) << "Address 1" << ": ";
    std::getline(std::cin, this->cusDetail.address.address1);
    std::cout << std::setw(w20) << "Address 2" << ": ";
    std::getline(std::cin, this->cusDetail.address.address2);
    std::cout << std::setw(w20) << "City" << ": ";
    std::getline(std::cin, this->cusDetail.address.city);
    std::cout << std::setw(w20) << "State" << ": ";
    std::getline(std::cin, this->cusDetail.address.state);
    std::cout << std::setw(w20) << "Postal Code" << ": ";
    std::cin >> this->cusDetail.address.postalCode;
    std::cin.ignore();
    std::cout << std::setw(w20) << "Country" << ": ";
    std::getline(std::cin, this->cusDetail.address.country);
}

void Customer::add_newCustomer()
{
    std::string sql;
    sql = "INSERT INTO CUSTOMER VALUES(NULL,\"" + this->cusDetail.name + "\",\"" \
          + this->cusDetail.address.address1 + "\",\"" + this->cusDetail.address.address2 \
          + "\",\"" + this->cusDetail.address.city + "\",\"" + this->cusDetail.address.state \
          + "\"," + std::to_string(this->cusDetail.address.postalCode) + ",\"" \
          + this->cusDetail.address.country + "\");";
    this->database.exec_db(sql);
    sql = "SELECT customerID FROM CUSTOMER WHERE customerName=\"" \
          + this->cusDetail.name + "\";";
    int id;
    id = this->database.get_int(sql);
    sql = "INSERT INTO PHONE VALUES(NULL," + std::to_string(id) + "," \
          + std::to_string(this->cusDetail.phone) + ");";
    this->database.exec_db(sql);
}

void Customer::list_cusName()
{
    std::string sql;
    sql = "SELECT CUSTOMERID, CUSTOMERNAME FROM CUSTOMER;";
    this->database.get_table(sql);
}

void Customer::search_cusInfo(int customerID)
{
    std::cout << "\n";
    std::cout << "-------------------\n";
    std::cout << "| Customer Detail |\n";
    std::cout << "-------------------\n\n";
    std::string sql;
    sql = "SELECT CUSTOMERID AS 'CUSTOMER ID', CUSTOMERNAME AS 'CUSTOMER NAME'"
          ", ADDRESS1 AS 'ADDRESS 1', ADDRESS2 AS 'ADDRESS 2', CITY AS 'CITY'"
          ", STATE AS 'STATE', POSTALCODE AS 'POSTAL CODE', COUNTRY AS 'COUNTRY'"
          " FROM CUSTOMER WHERE CUSTOMERID=" + std::to_string(customerID) + ";";
    this->database.get_info(sql);
    sql = "SELECT PHONENUM AS 'PHONE (+60)' FROM PHONE JOIN CUSTOMER ON CUSTOMER.CUSTOMERID"
          "=PHONE.CUSTOMERID WHERE PHONE.CUSTOMERID=" + std::to_string(customerID) + ";";
    this->database.get_phoneNum(sql);
}

void Customer::add_phone(int customerID)
{
    std::string sql;
    std::cout << "Enter New Phone Number: ";
    std::cin >> this->upPhone;
    std::cin.ignore();
    sql = "INSERT INTO PHONE(CUSTOMERID, PHONENUM) VALUES(" 
          + std::to_string(customerID) + "," + std::to_string(this->upPhone)
          + ");";
    this->database.exec_db(sql);
}

void Customer::delete_phone(int customerID) {
    std::string sql;
    int phoneDel;
    sql = "SELECT PHONENUM FROM PHONE WHERE CUSTOMERID="
          + std::to_string(customerID) + ";";
    this->database.get_table(sql);
    std::cout << "\n";
    std::cout << "Enter the Phone Number to be DELETED: ";
    std::cin >> phoneDel;
    std::cin.ignore();
    sql = "DELETE FROM PHONE WHERE PHONENUM=" + std::to_string(phoneDel) + ";";
    this->database.exec_db(sql);
}

void Customer::update_address(int customerID)
{
    std::string sql;
    std::cout << std::setw(w20) << "Address 1" << ": ";
    std::getline(std::cin, this->upAddress.address1);
    std::cout << std::setw(w20) << "Address 2" << ": ";
    std::getline(std::cin, this->upAddress.address2);
    std::cout << std::setw(w20) << "City" << ": ";
    std::getline(std::cin, this->upAddress.city);
    std::cout << std::setw(w20) << "State" << ": ";
    std::getline(std::cin, this->upAddress.state);
    std::cout << std::setw(w20) << "Postal Code" << ": ";
    std::cin >> this->upAddress.postalCode;
    std::cin.ignore();
    std::cout << std::setw(w20) << "Country" << ": ";
    std::getline(std::cin, this->upAddress.country);
    sql = "UPDATE CUSTOMER SET ADDRESS1=\'" + this->upAddress.address1 + "\',"
          "ADDRESS2=\'" + this->upAddress.address2 + "\', CITY=\'" + this->upAddress.city
          + "\', STATE=\'" + this->upAddress.state + "\', POSTALCODE=" + std::to_string(this->upAddress.postalCode)
          + ", COUNTRY=\'" + this->upAddress.country + "\' WHERE CUSTOMERID=" + std::to_string(customerID) + ";";
    this->database.exec_db(sql);
}
