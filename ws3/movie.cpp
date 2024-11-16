//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-09 Creat this file
//Done on

//
#include <iomanip>
#include <sstream>
#include "movie.h"
#include "settings.h"
using namespace std;
namespace seneca{
    //provided function
    void Movie::display(std::ostream& out) const
    {
        if (g_settings.m_tableView)
        {
            out << "M | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(9) << this->getYear() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "]\n";
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

    Movie* Movie::createItem(const string &strMovie) {
        if (strMovie.empty() || strMovie[0] == '#') {
            throw "Not a valid movie.";
        }
        //instead of using find and substr, I use istringstream to get the title, year, and summary
        istringstream stream(strMovie);
        string title{}, yearStr{}, summary{};
        unsigned short year{};
        try {
            getline(stream, title, ',');
            trim(title);
            getline(stream, yearStr, ',');
            trim(yearStr);
            year = static_cast<unsigned short>(stoi(yearStr));
            getline(stream, summary);
            trim(summary);
        }catch(...){
            throw "Not a valid movie.";
        };
        //new a movie object and return it
        return new Movie(title, year, summary);
    }
}