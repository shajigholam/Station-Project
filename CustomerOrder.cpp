// Name: Samaneh Hajigholam
// Seneca Student ID: 119751220
// Seneca email: shajigholam@myseneca.ca
// Date of completion: Nov 15, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <string>
#include <iomanip>
#include <iostream>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds {
    size_t CustomerOrder::m_widthField = 1;
    //a custom 1-argument constructor that takes a reference to an unmodifiable string. This constructor uses a local Utilities object to extract the tokens from the string and populate the current instance.
    CustomerOrder::CustomerOrder(const std::string& str) : CustomerOrder()
    {
        Utilities util;
        size_t posOfItem;
        size_t next_pos = 0;
        bool more = true;
        m_name = trim(util.extractToken(str, next_pos, more));
        m_product = trim(util.extractToken(str, next_pos, more)); //here
        m_cntItem = 0;
        
        posOfItem = next_pos; //*

        while (more) {
            util.extractToken(str, next_pos, more);
            m_cntItem++;
        }
        m_lstItem = new Item*[m_cntItem];
        next_pos = posOfItem;
        more = true;
        for (size_t i = 0; i < m_cntItem; i++) {
            m_lstItem[i] = new Item(util.extractToken(str, next_pos, more));
        }

        m_widthField = std::max(m_widthField, util.getFieldWidth()); //here
    }
    CustomerOrder::~CustomerOrder()
    {
        for (size_t i = 0; i < m_cntItem; i++){
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
        m_lstItem = nullptr;
    }
    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
    {
        *this = std::move(src);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept
    {
        if (this != &src) {
            if (this->m_lstItem != nullptr) {
                for (size_t i = 0; i < m_cntItem; i++){
                    delete m_lstItem[i];
                }

                delete[] m_lstItem;
                m_lstItem = nullptr;
            }
            m_name = src.m_name;
            m_product = src.m_product;
            m_cntItem = src.m_cntItem;
            m_lstItem = src.m_lstItem;
            //no width!!! -_-
            src.m_name = "";
            src.m_product = "";
            src.m_cntItem = 0;
            src.m_lstItem = nullptr;
        }
        return *this;
    }

    CustomerOrder::CustomerOrder(const CustomerOrder& src)
    {
        throw "No Copying allowed.";
    }

    bool CustomerOrder::isOrderFilled() const
    {
        // returns true if all the items in the order have been filled; false otherwise
        for (size_t i = 0; i < m_cntItem; i++){
            if (!m_lstItem[i]->m_isFilled){
                return false;
            }
        }
        return true;
    }
    // returns true if all items specified by itemName have been filled. If the item doesn't exist in the order, this query returns true.
    bool CustomerOrder::isItemFilled(const std::string& itemName) const
    {
        for (size_t i = 0; i < m_cntItem; i++){
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled){
                return false;
            }
        }
        return true;
    }

    void CustomerOrder::fillItem(Station & station, std::ostream & os) {
        bool filled = false; //flag not to get duplicate values

        for(auto i=0u; i<m_cntItem && !filled ; ++i){
            if( m_lstItem[i]->m_itemName == station.getItemName() ) {
                if(!m_lstItem[i]->m_isFilled && station.getQuantity()>0){
                    station.updateQuantity();
                    m_lstItem[i]->m_isFilled = true;
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    filled = true;
                }
                else if (station.getQuantity() <=0 ){
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }
    void CustomerOrder::display(std::ostream& os) const
    {
        os << m_name << " - " << std::left << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++)
            os << "[" << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
               << std::left << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName << "- "
               << ((m_lstItem[i]->m_isFilled) ? "FILLED" : "TO BE FILLED") << std::endl; //leading 0s here
    }
}
