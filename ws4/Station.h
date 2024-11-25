//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-24 Creat this file
//Done on

//

#ifndef SENECA_STATION_H
#define SENECA_STATION_H
#include <string>


namespace seneca {
    class Station {
        //Instance Variables
        int id{};
        std::string m_name{};
        std::string m_description{};
        size_t m_serialNumber{};
        size_t m_items{};

        //Class Variable
        static size_t m_widthField;
        static int id_generator;

    public:
        Station(const std::string& record);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
}
#endif //SENECA_STATION_H
