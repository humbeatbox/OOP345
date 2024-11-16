//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-09 Creat this file
//Done on

//


#include <sstream>
#include <algorithm>
#include <stdexcept>
//#include <string>
#include "book.h"
#include "mediaItem.h"
using namespace std;
namespace seneca {
    Book::Book(const std::string& author, const std::string& title, const std::string& country, double price, unsigned short year, const std::string& summary)
            :MediaItem(title, summary, year), m_author(author), m_country(country), m_price(price) {};
    //supplied function don't modify
    void Book::display(std::ostream& out) const{
        if (g_settings.m_tableView)
        {
            out << "B | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_country << " | ";
            out << std::setw(4) << this->getYear() << " | ";
            out << std::left;
            if (g_settings.m_maxSummaryWidth > -1)
            {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();
                else
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else
                out << this->getSummary();
            out << std::endl;
        }
        else
        {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "] [";
            out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }
    // looks like Factory Pattern
    Book* Book::createItem(const std::string& strBook){
        if (strBook.empty() || strBook[0] == '#') {//first line is empty or being comment by #
            throw "Not a valid book.";
        }
        //looks usgin istringstream make life easier instead of find and substr
        istringstream stream(strBook);
        string author{}, title{}, country{}, priceStr{}, yearStr{}, summary{};
        double price{};
        unsigned short year{};
        try {
            getline(stream, author, ',');
            trim(author);
            getline(stream, title, ',');
            trim(title);
            getline(stream, country, ',');
            trim(country);
            getline(stream, priceStr, ',');
            trim(priceStr);
            //convert the string price to double
            price = stod(priceStr);
            getline(stream, yearStr, ',');
            //convert the string year to int
            /*
             *
             * */
            trim(yearStr);
            year = static_cast<unsigned short>(stoi(yearStr));
            getline(stream, summary, ',');
            trim(summary);
        }catch(...) {
            cout << "Error in parsing the book." << endl;
        }
        //all good then use the private constructor to create a new book
        return new Book(author, title, country, price, year, summary);
    }
}