//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-24 Creat this file
//Done on

//

#include <iostream>
#include "Utilities.h"

namespace seneca {
    char Utilities::m_delimiter{};
    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }
    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }
    char Utilities::getDelimiter() {
        return m_delimiter;
    }

    //extracts a token from string str referred to by the first parameter.
    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {

        //if a delimiter is found at next_pos (first position)
        if (str[next_pos] == m_delimiter) {
            more = false;
            throw "Delimiter found at next_pos";
        }
        std::string token{};
        size_t pos = str.find(m_delimiter, next_pos);//find the next delimiter set to pos

        if (pos != std::string::npos) {//if found the next delimiter
            token = str.substr(next_pos, pos - next_pos);//from next_pos to pos - next_pos()
            next_pos = pos + 1;//set the next_pos to pos + 1 then can start from the next delimiter to find the next after next delimiter
            more = true;
        } else {//handle the last token std::string::npos
            token = str.substr(next_pos);
            next_pos = str.length();
            more = false;
        }

        while (!token.empty() && token.front() == ' ')
            token.erase(0, 1);
        while (!token.empty() && token.back() == ' ')
            token.pop_back();

        //updates the current object's m_widthField data member if its current value is less than the size of the token extracted.
        //for aligning the output of the token extracted?
        if (m_widthField < token.length()){
            m_widthField = token.length();
        }

        return token;
    }


}