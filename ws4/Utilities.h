//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-24 Creat this file
//Done on

//

#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H
#include <string>

namespace seneca {
    class Utilities {
        //Instance Variable
        size_t m_widthField{1};
        //Class Variable
        static char m_delimiter;
    public:
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
    };
}
#endif //SENECA_UTILITIES_H
