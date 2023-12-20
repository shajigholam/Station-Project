// Name: Samaneh Hajigholam
// Seneca Student ID: 119751220
// Seneca email: shajigholam@myseneca.ca
// Date of completion: Nov 28, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Workstation.h"

namespace sdds {

    std::deque<CustomerOrder> g_pending{};
    std::deque<CustomerOrder> g_completed{};
    std::deque<CustomerOrder> g_incomplete{};

    //receives a reference to an unmodifiable reference to std::string and passes it to the Station base class.
    Workstation::Workstation(const std::string& str) : Station(str) {}

    //this modifier fills the order at the front of the queue if there are CustomerOrders in the queue; otherwise, does nothing
    void Workstation::fill(std::ostream& os)
    {
        if (!m_orders.empty())
        {
            m_orders.front().fillItem(*this, os);
        }
    }
    //attempts to move the order order at the front of the queue to the next station in the assembly line
    bool Workstation::attemptToMoveOrder()
    {
        //if the order requires no more service at this station or cannot be filled (not enough inventory), move it to the next station; otherwise do nothing
        bool moved = false;

        if (!m_orders.empty()) {
            if ( m_orders.front().isItemFilled(this->getItemName()) || this->getQuantity() <= 0) {
                //if an order has been moved, return true; false otherwise.
                if (m_pNextStation) {
                    *m_pNextStation += std::move(m_orders.front());
                }
                //if there is no next station in the assembly line, then the order is moved into g_completed or g_incomplete queue
                else {
                    if (m_orders.front().isOrderFilled()) {
                        g_completed.push_back(std::move(m_orders.front()));
                    }
                    else {
                        g_incomplete.push_back(std::move(m_orders.front()));
                    }
                }
                m_orders.pop_front();
                moved = true;
            }
        }
        return moved;
    }
    void Workstation::setNextStation(Workstation* station)
    {
        m_pNextStation = station;
    }
    Workstation* Workstation::getNextStation() const
    {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream & os) const
    {
        os << this->getItemName() << " --> ";
        
        if(getNextStation()){
            os << getNextStation()->getItemName() << '\n';
        }
        else {
            os << "End of Line\n";
        }
    }
    Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
    {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
}
