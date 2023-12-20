// Name: Samaneh Hajigholam
// Seneca Student ID: 119751220
// Seneca email: shajigholam@myseneca.ca
// Date of completion: Nov 9, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>

namespace sdds {
    class Station {
        int m_id;
        std::string m_stationName;
        std::string m_description;
        size_t m_nextSerialNum;
        size_t m_numStockItems;
        static size_t m_widthField;
        static size_t id_generator;
      public:
        Station(const std::string& line);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity();
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
    //size_t m_widthField{0u};
    //size_t id_generator{0u};
}

#endif
