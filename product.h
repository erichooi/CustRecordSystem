#ifndef PRODUCT_H
#define PRODUCT_H 

#include <iostream>
#include "database.h"
#include "constant.h"


struct productDetail {
    std::string productName;
    std::string productCode;
    float price;
};

class Product {
    private:
        productDetail proDetail;
        SQLite database{dbName};
    public:
        Product();
        ~Product();
        void main();
        void search();
        void update();
        std::string get_productName(int);
        void set_proDetail();
        void add_newProduct();
        void list_productID();
        void search_productInfo(int);
        void update_price(int);
};


#endif /* ifndef PRODUCT_H */
