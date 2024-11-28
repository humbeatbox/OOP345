//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-24 Creat this file
//Done on

//

#include <iostream>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace seneca{
    size_t CustomerOrder::m_widthField = 0;//instance the static member

    CustomerOrder::CustomerOrder(const std::string &input) {
        Utilities ut;
        size_t next_pos = 0;
        bool more = true;

        m_name = ut.extractToken(input, next_pos, more);


        m_product = ut.extractToken(input, next_pos, more);

        //for item
        {
            //2D array extract the string from 1D
            size_t count_pos = next_pos;
//            size_t item_count{};//start from which item
            bool more_items = true;

            //count the number of items first
            while (more_items) {
                //extract the item name from second D with the delimiter(input)
                ut.extractToken(input, count_pos, more_items);
                m_cntItem++;
            }

            //allocate the memory for the item(have item_count items)
            m_lstItem = new Item*[m_cntItem];

            //extract the item name from second D with the delimiter(input)
            {
                for (size_t i = 0; i < m_cntItem && more; i++) {
                    std::string item_name = ut.extractToken(input, next_pos, more);
                    //use the extracted item name to create the item object
                    m_lstItem[i] = new Item(item_name);
                }
                //align the output size
                if (m_widthField < ut.getFieldWidth()) {
                    m_widthField = ut.getFieldWidth();
                }
            }


        }
    }

    CustomerOrder::CustomerOrder(const CustomerOrder &) {
        throw "Cannot make copies";
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
        *this = std::move(src);
    }

    CustomerOrder &CustomerOrder::operator=(CustomerOrder&& src) noexcept {
        if (this == &src) {
            return *this;
        }

        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;

        m_name = std::move(src.m_name);
        m_product = std::move(src.m_product);
        m_cntItem = src.m_cntItem;
        m_lstItem = src.m_lstItem;

        src.m_cntItem = 0;
        src.m_lstItem = nullptr;

        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
        m_lstItem = nullptr;
    }

    bool CustomerOrder::isOrderFilled() const {
        for (auto i = 0; i < m_cntItem; i++) {
            if (!m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return false;
    }

    bool CustomerOrder::isItemFilled(const std::string &itemName) const {

        //not exist and (exist and fulfilled) return true
        //exist and not fulfilled return false
        for (auto i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == itemName) {
                //exist and not fulfilled
                if (!m_lstItem[i]->m_isFilled) {
                    return false;
                }
            }
        }
        return true;
    }

    void CustomerOrder::fillItem(Station &station, std::ostream &os) {
        for (size_t i = 0; i < m_cntItem; i++) {//loop all items ,if the order doesn't contain the item handled, this function does nothing
            if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {//check the item name match the station and the item is not filled
                if (station.getQuantity() > 0) {//contains at least one item

                    //update the quantity item--
                    station.updateQuantity();
                    //update the serial number
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    //fill the item
                    m_lstItem[i]->m_isFilled = true;

                    //special output
                    os << "    Filled " << m_name << ", " << m_product << " ["
                       << m_lstItem[i]->m_itemName << "]" << std::endl;
                    return;
                }
                else {
                    os << "    Unable to fill " << m_name << ", " << m_product
                       << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream &os) const {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++) {
            os << "[" << std::setw(6) << std::setfill('0') << std::right
               << m_lstItem[i]->m_serialNumber << "] "
               << std::setw(m_widthField) << std::setfill(' ') << std::left
               << m_lstItem[i]->m_itemName << " - "
               << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }
}
