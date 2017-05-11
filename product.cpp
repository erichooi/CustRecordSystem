#include <iostream>
#include <iomanip>
#include <string>
#include "product.h"
#include "constant.h"
#include "database.h"
#include "util.h"
#include "interface.h"


Product::Product() {};

Product::~Product() {};

// wrapper for add new product
void Product::main()
{
    this->set_proDetail();
    this->add_newProduct();
}

// wrapper for search product
void Product::search()
{
    int productID;
    this->list_productID();
    std::cout << "Enter the product's ID: ";
    std::cin >> productID;
    std::cin.ignore();
    clrscreen();
    this->search_productInfo(productID);
}

// wrapper for update product
void Product::update()
{
    Interface product_interface;
    int productID;
    std::string productName;
    this->list_productID();
    std::cout << "Enter the product's ID: ";
    std::cin >> productID;
    std::cin.ignore();
    productName = this->get_productName(productID);
    clrscreen();
    product_interface.product_update_page(productName);
    clrscreen();
    switch (product_interface.get_choice()) {
        case 'a':
            this->update_price(productID);
            break;
    }
}

std::string Product::get_productName(int productID) 
{
    std::string sql, productName;
    sql = "SELECT PRODUCTNAME FROM PRODUCT WHERE PRODUCTID=" 
          + std::to_string(productID) + ";";
    productName = this->database.get_str(sql);
    return productName;
}

void Product::set_proDetail()
{
    DBFlag flag = DBFlag::PRO_FLAG;
    int duplicate;
    bool endFlag = false;
    std::cout << std::left;
    do {
        std::cout << "\n";
        std::cout << "---------------------------\n";
        std::cout << "| New Product Information |\n";
        std::cout << "---------------------------\n\n";
        std::cout << std::setw(w20) << "Product Name" << ": ";
        std::getline(std::cin, this->proDetail.productName);

        duplicate = this->database.detect_duplication(flag, this->proDetail.productName);
        if (duplicate == 1) {
            show_dialog("DUPLICATE data detected!");
            clrscreen();
        } else {
            endFlag = true;
        }
    } while (endFlag == false);
    std::cout << std::setw(w20) << "Product Code" << ": ";
    std::getline(std::cin, this->proDetail.productCode);
    std::cout << std::setw(w20) << "Price" << ": RM ";
    std::cin >> this->proDetail.price;
    std::cin.ignore();
}

void Product::add_newProduct()
{
    std::string sql;
    sql = "INSERT INTO PRODUCT VALUES(NULL,\"" + this->proDetail.productName \
          + "\",\"" + this->proDetail.productCode + "\"," \
          + std::to_string(this->proDetail.price) + ");";
    this->database.exec_db(sql);
}

void Product::list_productID()
{
    std::string sql;
    sql = "SELECT PRODUCTID, PRODUCTNAME, PRODUCTCODE FROM PRODUCT;";
    this->database.get_table(sql);
}

void Product::search_productInfo(int productID)
{
    std::string sql;
    std::cout << "\n";
    std::cout << "------------------\n";
    std::cout << "| Product Detail |\n";
    std::cout << "------------------\n\n";
    sql = "SELECT PRODUCT.PRODUCTID AS 'PRODUCT ID', PRODUCT.PRODUCTNAME AS"
          " 'PRODUCT NAME', PRODUCT.PRODUCTCODE AS 'PRODUCT CODE', PRODUCT.PRICE"
          " AS 'PRODUCT PRICE (RM)' FROM PRODUCT WHERE PRODUCTID=" 
          + std::to_string(productID) + ";";
    this->database.get_info(sql);
}

void Product::update_price(int productID) 
{
    std::string sql;
    float newPrice;
    std::cout << "Enter the new price: ";
    std::cin >> newPrice;
    std::cin.ignore();
    sql = "UPDATE PRODUCT SET PRICE=" + std::to_string(newPrice) + " WHERE PRODUCTID="
          + std::to_string(productID) + ";";
    this->database.exec_db(sql);
}
