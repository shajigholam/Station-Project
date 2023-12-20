// Name: Samaneh Hajigholam
// Seneca Student ID: 119751220
// Seneca email: shajigholam@myseneca.ca
// Date of completion: Nov 15, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

//The CustomerOrder module contains all the functionality for processing customer orders as they move from Station to Station along the assembly line. The Station where a given order currently rests fills a request for one item of that station, if there is any such request.

#ifndef SDDS_CUSTOMER_ORDER_H
#define SDDS_CUSTOMER_ORDER_H
#include <iostream>
#include <string>
#include "Station.h"

namespace sdds {
    struct Item {
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};
        Item(const std::string& src) : m_itemName(src) {};
    };

    class CustomerOrder {
        std::string m_name{}; //the name of the customer
        std::string m_product{}; //the name of the product being assembled
        size_t m_cntItem{}; //a count of the number of items in the customer's order
        Item** m_lstItem = nullptr; // a dynamically allocated array of pointers. Each element of the array points to a dynamically allocated object of type Item
        static size_t m_widthField;
      public:
        CustomerOrder(){}
        CustomerOrder(const std::string&);
        CustomerOrder(const CustomerOrder&);
        CustomerOrder& operator=(const CustomerOrder&)=delete;
        CustomerOrder(CustomerOrder&&) noexcept;
        CustomerOrder& operator=(CustomerOrder&&) noexcept;
        ~CustomerOrder();
        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
    };
}

#endif
