//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-09 Creat this file
//Done on

//

#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H
#include <string>
#include "mediaItem.h"
#include "settings.h"
#include <iostream>
#include <iomanip>

namespace seneca {
    class Book : public MediaItem {
        std::string m_author{};
        //title (inherited)
        std::string m_country{};
        //the year of publication (inherited)
        double m_price{};
        //the summary (inherited)

        Book(const std::string& author, const std::string& title, const std::string& country, double price, unsigned short year, const std::string& summary);
    public:
        void display(std::ostream& out) const override;
        static Book* createItem(const std::string& strBook);
    };
}
#endif //SENECA_BOOK_H
