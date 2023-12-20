// Name: Samaneh Hajigholam
// Seneca Student ID: 119751220
// Seneca email: shajigholam@myseneca.ca
// Date of completion: Nov 20, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <deque>
#include <iostream>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds {

extern std::deque<CustomerOrder> g_pending; //holds the orders to be placed onto the assembly line at the first station.
extern std::deque<CustomerOrder> g_completed; //holds the orders that have been removed from the last station and have been completely filled.
extern std::deque<CustomerOrder> g_incomplete; //holds the orders that have been removed from the last station and could not be filled completely.

class Workstation : public Station {
    std::deque<CustomerOrder> m_orders; //is a double-ended-queue with CustomerOrders entering the back and exiting the front. These are orders that have been placed on this station to receive service (or already received service).
    Workstation* m_pNextStation{}; //a pointer to the next Workstation on the assembly line.
public:
    // Since a Workstation object represents a single location on the assembly line for filling customer orders with items, the object cannot be copied or moved.
    Workstation(const Workstation& src) = delete;
    Workstation& operator=(const Workstation& src) = delete;
    Workstation(Workstation&& src) = delete;
    Workstation& operator=(Workstation&& src) = delete;
    Workstation(const std::string& str);
    void fill(std::ostream& os);
    bool attemptToMoveOrder();
    void setNextStation(Workstation* station = nullptr);
    Workstation* getNextStation() const;
    void display(std::ostream& os) const;
    Workstation& operator+=(CustomerOrder&& newOrder);
};
}
#endif /* Workstation_h */
