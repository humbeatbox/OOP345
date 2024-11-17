//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-09 Creat this file
//Done on

//

#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H
#include <string>
#include <iostream>

namespace seneca {
    class SpellChecker {
        std::string m_badWords[6];
        std::string m_goodWords[6];
        size_t m_replacements[6] = {0};

    public:
        // Constructor that loads bad/good words from a file
        SpellChecker(const char* filename);

        // Overloaded function call operator to correct text
        void operator()(std::string& text);

        // Function to display statistics of replacements
        void showStatistics(std::ostream& out) const;
    };
}

#endif //SENECA_SPELLCHECKER_H
