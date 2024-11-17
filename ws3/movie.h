//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-09 Creat this file
//Done on

//

#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H
#include "mediaItem.h"

namespace seneca {

    class Movie : public MediaItem {
//        title (inherited)
//        the year of release (inherited)
//        the summary (inherited)

        //private constructor
        Movie( const std::string &title, unsigned short year, const std::string &summary):MediaItem(title, summary, year) {};

    public:
        static Movie* createItem(const std::string& strMovie);
        void display(std::ostream& out) const override;
    };

}
#endif //SENECA_MOVIE_H
