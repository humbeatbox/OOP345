//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-24 Creat this file
//Done on

//
#include <iomanip>
#include <iostream>
#include "Station.h"
#include "Utilities.h"
namespace seneca{
    size_t Station::m_widthField = 0;//for aligning the output of the token extracted
    int Station::id_generator = 0;//for generating the station id and Initial value is 0.

    Station::Station(const std::string &record) {
        Utilities ut{};
        size_t next_pos{};//for position
        bool more{};//for checking have more token or not
        id = ++id_generator;//generate the station id

        //extract the station name
        m_name = ut.extractToken(record, next_pos, more);
        //align the output
        if (m_widthField < ut.getFieldWidth()) {
            m_widthField = ut.getFieldWidth();
        }
        //extract the serial number and convert it to size_t and assign it to m_serialNumber
        m_serialNumber = static_cast<size_t>(std::stoi(ut.extractToken(record, next_pos, more)));
        //extract the quantity and convert it to size_t and assign it to m_items
        m_items = static_cast<size_t>(std::stoi(ut.extractToken(record, next_pos, more)));
        //extract the description
        m_description = ut.extractToken(record, next_pos, more);

    }

    const std::string &Station::getItemName() const {
        return m_name;
    }

    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const {
        return m_items;
    }

    void Station::updateQuantity() {
        if (m_items > 0) {
            m_items--;
        }
    }

    void Station::display(std::ostream &os, bool full) const {
        os << std::setw(3) << std::setfill('0') << std::right << id << " | "
           << std::setw(static_cast<int>(m_widthField)) << std::setfill(' ') << std::left << m_name << " | "
           << std::setw(6) << std::setfill('0') << std::right << m_serialNumber << " | ";

        if (full) {
            os << std::setw(4) << std::setfill(' ') << std::right << m_items << " | "
               << m_description;
        }

        os << std::endl;
    }


}