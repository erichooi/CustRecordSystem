/** 
 * Execution file for system 
 **/
#include <iostream>
#include "customer.h"
#include "product.h"
#include "orders.h"
#include "interface.h"
#include "util.h"
#ifdef _WIN32
#include "Windows.h"
#endif


int main(int argc, char *argv[])
{
#ifdef _WIN32
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
#endif
    Interface main;
    Customer cust;
    Product prod;
    Orders ord;
    char choice;
    int Q_FLAG = 0;

    clrscreen();
    main.disclaimer();
    //sleep();

    while (Q_FLAG != 1) {
        clrscreen();
        main.main_page();
        choice = main.get_choice();
        clrscreen();

        switch (choice) {
            case 'a':
                cust.main();
                Q_FLAG = quit_loop();
                break;
            case 'b':
                prod.main();
                Q_FLAG = quit_loop();
                break;
            case 'c':
                ord.main();
                Q_FLAG = quit_loop();
                break;
            case 'd':
                main.search_page();
                choice = main.get_choice();
				clrscreen();
                if (choice == 'a') {
                    cust.search();
                } else if (choice == 'b') {
                    prod.search();
                } else if (choice == 'c') {
                    main.order_search_page();
                    choice = main.get_choice();
                    clrscreen();
                    if (choice == 'a') {
                        ord.search(SFlag::NAME_FLAG);
                    } else if (choice == 'b') {
                        ord.search(SFlag::DATE_FLAG);
                    } else if (choice == 'c') {
                        ord.search(SFlag::ORDERID_FLAG);
                    }
                }
                Q_FLAG = quit_loop();
                break;
			case 'e':
				main.information_page();
				choice = main.get_choice();
				clrscreen();
				if (choice == 'a') {
                    cust.update();
				} else if (choice == 'b') {
                    prod.update();
                } else if (choice == 'c') {
                    ord.update();
                }
                Q_FLAG = quit_loop();
				break;
        }
    }
    
    return 0;
}
