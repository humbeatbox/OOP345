//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-09-17 Creat this file
//Done on

#include <fstream>
#include <sstream>
#include <iostream>

#include <iomanip>
#include "dictionary.h"
#include "settings.h"

using namespace seneca;
using namespace std;
namespace seneca{
    Dictionary::Dictionary() {

    }
    Dictionary::Dictionary(const char *filename){
        size_t index{};
        ifstream file(filename);
        if (!file) {
            return;
        }
        string line{};

        while (getline(file, line)){
            m_size++;
        }

        file.clear();
        file.seekg(0);
        m_words = new Word[m_size];
        while (getline(file, line)&& index<m_size ) {

            stringstream ss(line);
            string word, posStr, definition;

            getline(ss, word, ',');
            getline(ss, posStr, ',');
            getline(ss, definition);

            m_words[index].m_word = word;
            m_words[index].m_definition = definition;
            m_words[index].m_pos = transfertoPType(posStr);
            index++;

        }
    }

    Dictionary::~Dictionary() {
        delete[] m_words;
    }

    Dictionary::Dictionary(const Dictionary &other){
        *this = other;
    }

    Dictionary &Dictionary::operator=(const Dictionary &other) {
        if (this == &other) {
            return *this;
        }

        if (other.m_size > 0) {
            delete[] m_words;
            m_size = other.m_size;
            m_words = new Word[other.m_size];
            for (size_t i = 0; i < m_size; ++i) {
                m_words[i] = other.m_words[i];
            }
        }

        return *this;
    }

    Dictionary::Dictionary(Dictionary&& other) noexcept{
        *this = std::move(other);
    }
    Dictionary& Dictionary::operator=(Dictionary&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete[] m_words;
        m_words = other.m_words;
        m_size = other.m_size;
        //move
        other.m_words = nullptr;
        other.m_size = 0;

        return *this;
    }

    void Dictionary::searchWord(const char *word) const {
        bool ffound{};

        for(size_t i =0; i < m_size ;i++){
            if(m_words[i].m_word == word){//match the word
                if (!ffound) {//first time print. first line
                    cout << m_words[i].m_word;
                    if (g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown) {
                        cout << " - (" << transferPTypeToString(m_words[i].m_pos) << ") ";
                    } else {
                        cout << " - ";
                    }
                    cout << m_words[i].m_definition << endl;
                    ffound = true;
                }else{//not first time print
                    cout << setw(m_words[i].m_word.length()) << right << " " << " - " ;
                    if (g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown) {
                        cout << "(" << transferPTypeToString(m_words[i].m_pos) << ") ";
                    }
                    cout << m_words[i].m_definition << endl;
                }
                //if true will only show first line(stop the loop)
                if(!g_settings.m_show_all){
                    return;
                }

            }

        }
        if (!ffound){//no found
            cout << "Word '" << word << "' was not found in the dictionary." << endl;
        }

    }


    string Dictionary::transferPTypeToString(const PartOfSpeech pos) const {
        switch(pos) {
            case PartOfSpeech::Noun:
                return "noun";
            case PartOfSpeech::Pronoun:
                return "pronoun";
            case PartOfSpeech::Adjective:
                return "adjective";
            case PartOfSpeech::Adverb:
                return "adverb";
            case PartOfSpeech::Verb:
                return "verb";
            case PartOfSpeech::Preposition:
                return "preposition";
            case PartOfSpeech::Conjunction:
                return "conjunction";
            case PartOfSpeech::Interjection:
                return "interjection";
            case PartOfSpeech::Unknown:
            default:
                return "unknown";
        }
    }

    PartOfSpeech Dictionary::transfertoPType(const std::string posStr) const {
        if (posStr == "n." || posStr == "n. pl.") return PartOfSpeech::Noun;
        if (posStr == "adv.") return PartOfSpeech::Adverb;
        if (posStr == "a.") return PartOfSpeech::Adjective;
        if (posStr == "v." || posStr == "v. i." || posStr == "v. t." || posStr == "v. t. & i.") return PartOfSpeech::Verb;
        if (posStr == "prep.") return PartOfSpeech::Preposition;
        if (posStr == "pron.") return PartOfSpeech::Pronoun;
        if (posStr == "conj.") return PartOfSpeech::Conjunction;
        if (posStr == "interj.") return PartOfSpeech::Interjection;
        return PartOfSpeech::Unknown;
    }


}