//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-28 Creat this file
//Done on

//
#include <iostream>
#include "Workstation.h"

namespace seneca{
    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    Workstation::Workstation(const std::string &data) : Station(data) {}

    //this modifier fills the order at the front of the queue
    //if there are CustomerOrders in the queue; otherwise, does nothing.
    void Workstation::fill(std::ostream &os) {
        if (!m_orders.empty()) {
            m_orders.front().fillItem(*this, os);
        }
    }

    //this modifier stores the address of the referenced Workstation object
    // in the pointer to the m_pNextStation.
    //Parameter defaults to nullptr
    void Workstation::setNextStation(Workstation *station) {
        m_pNextStation = station;
    }
    //returns the address of next Workstation
    Workstation *Workstation::getNextStation() const {
        return m_pNextStation;
    }

    Workstation &Workstation::operator+=(CustomerOrder &&newOrder) {
        m_orders.push_back(std::move(newOrder));//push to back
        return *this;
    }


    bool Workstation::attemptToMoveOrder() {
        if (m_orders.empty()) {
            return false;
        }

        CustomerOrder& currentOrder = m_orders.front();

        if (currentOrder.isItemFilled(getItemName()) || getQuantity() <= 0) {
            if (m_pNextStation) {
                *m_pNextStation += std::move(currentOrder);
            } else {
                bool is_filled = currentOrder.isOrderFilled();
                if (is_filled) {
                    g_completed.push_back(std::move(currentOrder));
                } else {
                    g_incomplete.push_back(std::move(currentOrder));
                }
            }
            m_orders.pop_front();
            return true;
        }
        return false;
    }

    void Workstation::display(std::ostream &os) const {
        os << getItemName() << " --> ";
        os << (m_pNextStation ? m_pNextStation->getItemName() : "End of Line");
        os << std::endl;
    }
}