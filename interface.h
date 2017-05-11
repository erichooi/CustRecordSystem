#ifndef INTERFACE_H
#define INTERFACE_H 


#include <iostream>


class Interface {
    private:
        char choice;
    public:
        Interface();
        ~Interface();
        void disclaimer();
        void main_page();
        void search_page();
        void order_search_page();
        void information_page();
        void customer_update_page(std::string);
        void customer_update_phone_page();
        void product_update_page(std::string);
        void order_update_page(int);
        void order_update_status_page();
        char get_choice();
};

#endif /* ifndef INTERFACE_H */
