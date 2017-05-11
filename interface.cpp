#include <iostream>
#include <iomanip>
#include <string>
#include "interface.h"

Interface::Interface() {};

Interface::~Interface() {};

void Interface::disclaimer()
{
    std::cout << "\n";
    std::cout << "---------- DISCLAIMER ----------\n";
    std::cout << "All the currency that use in this program is Ringgit Malaysia (RM).\n";
    std::cout << "Thank and hope you enjoy the program.\n";
}

void Interface::main_page()
{
    std::cout << "\n";
    std::cout << "--------------------------\n";
    std::cout << "| Customer Record System |\n";
    std::cout << "--------------------------\n\n";
    std::cout << "a) Enter New Customer" << std::endl;
    std::cout << "b) Enter New Product" << std::endl;
    std::cout << "c) Enter New Order" << std::endl;
    std::cout << "d) Search" << std::endl;
    std::cout << "e) Update Information\n\n";
    std::cout << "Enter your choice: ";
    std::cin >> this->choice;
    std::cin.ignore();
}

void Interface::search_page()
{
    std::cout << "\n";
    std::cout << "--------------------\n";
    std::cout << "| Record Searching |\n";
    std::cout << "--------------------\n\n";
    std::cout << "a) Customer Record" << std::endl;
    std::cout << "b) Product Record" << std::endl;
    std::cout << "c) Order Record" << std::endl;
    std::cout << "\n";
    std::cout << "Enter your choice: ";
    std::cin >> this->choice;
    std::cin.ignore();
}

void Interface::order_search_page()
{
    std::cout << "\n";
    std::cout << "-------------------\n";
    std::cout << "| Order Searching |\n";
    std::cout << "-------------------\n\n";
    std::cout << "a) Search by Name" << std::endl;
    std::cout << "b) Search by Date" << std::endl;
    std::cout << "c) Search by OrderID" << std::endl;
    std::cout << "\n";
    std::cout << "Enter your choice: ";
    std::cin >> this->choice;
    std::cin.ignore();
}

void Interface::information_page()
{
    std::cout << "\n";
    std::cout << "----------------------\n";
    std::cout << "| Information Update |\n";
    std::cout << "----------------------\n\n";
    std::cout << "a) Customer" << std::endl;
    std::cout << "b) Product" << std::endl;
    std::cout << "c) Order" << std::endl;
    std::cout << "\n";
    std::cout << "Enter your choice: ";
    std::cin >> this->choice;
    std::cin.ignore();
}

void Interface::customer_update_page(std::string customerName)
{
    std::cout << "\n";
    std::cout << "-------------------\n";
    std::cout << "| Customer Update |\n";
    std::cout << "-------------------\n\n";
    std::cout << "Customer's Name: " << customerName << "\n\n";
    std::cout << "a) Phone Number" << std::endl;
    std::cout << "b) Address" << std::endl;
    std::cout << "\n";
    std::cout << "Enter your choice: ";
    std::cin >> this->choice;
    std::cin.ignore();
}

void Interface::customer_update_phone_page()
{
    std::cout << "\n";
    std::cout << "----------------\n";
    std::cout << "| Phone Number |\n";
    std::cout << "----------------\n\n";
    std::cout << "a) Add" << std::endl;
    std::cout << "b) Delete" << std::endl;
    std::cout << "\n";
    std::cout << "Enter your choice: ";
    std::cin >> this->choice;
    std::cin.ignore();
}

void Interface::product_update_page(std::string productName)
{
    std::cout << "\n";
    std::cout << "------------------\n";
    std::cout << "| Product Update |\n";
    std::cout << "------------------\n\n";
    std::cout << "Product's Name: " << productName << "\n\n";
    std::cout << "a) Price" << std::endl;
    std::cout << "\n";
    std::cout << "Enter your choice: ";
    std::cin >> this->choice;
    std::cin.ignore();
}

void Interface::order_update_page(int orderID) 
{
    std::cout << "\n";
    std::cout << "----------------\n";
    std::cout << "| Order Update |\n";
    std::cout << "----------------\n\n";
    std::cout << "Order's ID: " << orderID << "\n\n";
    std::cout << "a) Status" << std::endl;
    std::cout << "b) Add product" << std::endl;
    std::cout << "c) Delete product" << std::endl;
    std::cout << "\n";
    std::cout << "Enter your choice: ";
    std::cin >> this->choice;
    std::cin.ignore();
}

void Interface::order_update_status_page()
{
    std::cout << "\n";
    std::cout << "----------\n";
    std::cout << "| Status |\n";
    std::cout << "----------\n\n";
    std::cout << "a) Complete" << std::endl;
    std::cout << "b) Cancel" << std::endl;
    std::cout << "\n";
    std::cout << "Enter your choice: ";
    std::cin >> this->choice;
    std::cin.ignore();
}

char Interface::get_choice()
{
    return this->choice;
}
