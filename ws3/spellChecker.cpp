//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-09 Creat this file
//Done on

//

#include "spellChecker.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
using namespace std;
namespace seneca {
    SpellChecker::SpellChecker(const char* filename) {
        ifstream file(filename);
        if (!file) {
            throw "Bad file name!";
        }
        string line;
        size_t index = 0;

        while (std::getline(file, line) && index < 6) {
            istringstream stream(line);
            stream >> m_badWords[index] >> m_goodWords[index];
            index++;
        }
    }

    void SpellChecker::operator()(std::string &text) {
        for (size_t i = 0; i < 6; ++i) {
            size_t pos = text.find(m_badWords[i]);
            while (pos != string::npos) {//search everything in the text string::npos means the end of the string
                text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
                m_replacements[i]++;//count how many times the word is replaced
                pos = text.find(m_badWords[i], pos + m_goodWords[i].length());
            }
        }
    }

    void SpellChecker::showStatistics(std::ostream &out) const {
        for (size_t i = 0; i < 6; ++i) {
            out << right << setw(15) << m_badWords[i] << ": " << m_replacements[i] << " replacements" << endl;
        }
    }
}