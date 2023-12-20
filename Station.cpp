// Name: Samaneh Hajigholam
// Seneca Student ID: 119751220
// Seneca email: shajigholam@myseneca.ca
// Date of completion: Nov 9, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Station.h"
#include "Utilities.h"
#include <string>
#include <iostream>
#include <iomanip>

namespace sdds {
    size_t Station::m_widthField = 0; //added
    size_t Station::id_generator = 0; //added
    Station::Station(const std::string& line) {
        Utilities token;
        size_t nextPos = 0;
        bool more = true;
        m_id = ++id_generator;

        m_stationName = token.extractToken(line, nextPos, more);
        if (more)
            m_nextSerialNum = stoi(token.extractToken(line, nextPos, more));
        if (more)
            m_numStockItems = stoi(token.extractToken(line, nextPos, more));
        
        if (more) {
            m_widthField = std::max(m_widthField, token.getFieldWidth());
            m_description = token.extractToken(line, nextPos, more);
        }

        m_stationName = trim(m_stationName);
    }
    
    const std::string& Station::getItemName() const {
        return m_stationName;
    }
    
    size_t Station::getNextSerialNumber() {
        return m_nextSerialNum++;
    }
    
    size_t Station::getQuantity() {
        return m_numStockItems;
    }
    
    void Station::updateQuantity() {
        if (m_numStockItems > 0)
            m_numStockItems--;
    }
    
    void Station::display(std::ostream& os, bool full) const {
        os << std::right << std::setw(3) << std::setfill('0') << m_id  << " | " << std::left << std::setfill(' ') << std::setw(m_widthField) << m_stationName
           << "| "<< std::right << std::setw(6) << std::setfill('0') << m_nextSerialNum << " | ";
        
        if (full) {
            os << std::setfill(' ') << std::setw(4) << m_numStockItems << " | " << m_description;
        }
        os << std::endl;
    }
}
