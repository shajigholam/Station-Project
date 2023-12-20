// Name: Samaneh Hajigholam
// Seneca Student ID: 119751220
// Seneca email: shajigholam@myseneca.ca
// Date of completion: Nov 30, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
// My constructor and reorderStations function didn't work properly, so I asked my friend and she got them from "https://github.com/furkanbass/OOP345-Project/blob/main/LineManager.cpp".
#include <fstream>
#include <algorithm>
#include <string>
#include "LineManager.h"
#include "Utilities.h"

namespace sdds {
    //this constructor receives the name of the file that identifies the active stations on the assembly line and the collection of workstations available for configuring the assembly line.
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    {
        std::ifstream filein(file);
        if (!filein) {
            throw std::string("Can't open ") + file;
        }
        std::string line;
        while (std::getline(filein, line))
        {
            std::string workstation = line.substr(0, line.find_first_of('|'));
            std::string nextWorkstation = line.erase(0, workstation.size() + 1);

            auto ws = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws1)
                {
                    return ws1->getItemName() == workstation;
                });
            m_activeLine.push_back(*ws);

            if (!nextWorkstation.empty())
            {
                for_each(stations.begin(), stations.end(), [=](Workstation* ws1)
                    {
                        if (ws1->getItemName() == nextWorkstation)
                        m_activeLine.back()->setNextStation(ws1);
                    });
            }
            else
            {
                m_activeLine.back()->setNextStation(nullptr);
            }
        }

        for_each(m_activeLine.begin(), m_activeLine.end(), [=](Workstation* ws)
            {
                auto first = std::find_if(m_activeLine.begin(), m_activeLine.end(), [=](Workstation* ws1)
                    {
                        return ws == ws1->getNextStation();
                    });
        if (first == m_activeLine.end())
        {
            m_firstStation = ws;
        }
            });

        m_cntCustomerOrder = g_pending.size();
    }

    void LineManager::reorderStations()
    {
        std::vector<Workstation*> reorder;

        reorder.push_back(m_firstStation);
        if (m_firstStation->getNextStation()) {
            reorder.push_back(m_firstStation->getNextStation());
        }

        std::for_each(m_activeLine.begin(), m_activeLine.end() - 2, [&](Workstation* ws)
            {
                reorder.push_back(reorder.back()->getNextStation());
            }); //added -2 - no valid next station after that

        m_activeLine = reorder;
    }

    bool LineManager::run(std::ostream & os)
    {
        //keeps track of the current iteration number (use a local variable)
        static size_t counter = 1;
        os << "Line Manager Iteration: " << counter++ << '\n';
        //moves the order at the front of the g_pending queue to the m_firstStation and remove it from the queue. This function moves only one order to the line on a single iteration.
        if(!g_pending.empty()){
            
            *m_firstStation += std::move(g_pending.front());
           
            g_pending.pop_front();
        }
        //for each station on the line, executes one fill operation
        for(auto& i : m_activeLine){
            i->fill(os);
        }
        //for each station on the line, attempts to move an order down the line
        for(auto& i : m_activeLine){
            i->attemptToMoveOrder();
        }
        //return true if all customer orders have been filled or cannot be filled, otherwise returns false
        return (m_cntCustomerOrder == g_completed.size() + g_incomplete.size());
    }
    void LineManager::display(std::ostream & os) const
    {
        for(auto& i : m_activeLine){
            i->display(os);
        }
    }
}
