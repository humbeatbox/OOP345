//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-09-17 Creat this file
//Done on

//


#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include "dictionary.h"
#include "settings.h"

using namespace seneca;
using namespace std;
namespace seneca{

    Dictionary::Dictionary(){}


    Dictionary::Dictionary(const char *filename){
        int index{};
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

            std::stringstream ss(line);
            std::string word, posStr, definition;

            std::getline(ss, word, ',');
            std::getline(ss, posStr, ',');
            std::getline(ss, definition);


            m_words[index].m_word = word;
            m_words[index].m_definition = definition;
//            cout << "word is :" << m_words[index].m_word<< endl;
//            cout << "def is :" << m_words[index].m_definition << endl;
            //TODO make pos correct
            m_words[index].m_pos = transfertoPType(posStr);
//            if(m_words[index].m_pos == PartOfSpeech::Unknown){
//                cout << "pos is :" << "unknow" << endl;
//            }
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

//            cout << "word is :" << m_words[i].m_word<< endl;
//            cout << "def is :" << m_words[i].m_definition << endl;
//            cout << "pos is :" << transferPTypeToString(m_words[i].m_pos) << endl;
    void Dictionary::searchWord(const char *word) const {
        bool found = false;
        cout << word;
        for(size_t i =0; i < m_size ;i++){
            if(m_words[i].m_word == word){
                found = true;
                cout << setw(m_words[i].m_word.length()) << right <<" - (" << transferPTypeToString(m_words[i].m_pos) << ") " << m_words[i].m_definition << endl;
            }

        }


//        size_t wordLen = strlen(word);
//        size_t indent = wordLen + 3; // For proper indentation
/*
        for (size_t i = 0; i < m_size; ++i) {
//            if (strcasecmp((m_words[i].m_word).c_str(), word) == 0) {//compare the word
            cout << m_words[i].m_word ;
                if(m_words[i].m_word == word){

                if (!found) {
                    std::cout << m_words[i].m_word;
//                    if (g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown) {
//                        std::cout << " - (" << [this](PartOfSpeech pos) {
//                            switch (pos) {
//                                case PartOfSpeech::Noun: return "noun";
//                                case PartOfSpeech::Pronoun: return "pronoun";
//                                case PartOfSpeech::Adjective: return "adjective";
//                                case PartOfSpeech::Adverb: return "adverb";
//                                case PartOfSpeech::Verb: return "verb";
//                                case PartOfSpeech::Preposition: return "preposition";
//                                case PartOfSpeech::Conjunction: return "conjunction";
//                                case PartOfSpeech::Interjection: return "interjection";
//                                default: return "";
//                            }
//                        }(m_words[i].m_pos) << ")";
//                    }
//                    std::cout << " " << m_words[i].m_definition << std::endl;
                } else {
//                    std::cout << std::setw(indent) << " - ";
//                    if (g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown) {
//                        std::cout << "(" << [this](PartOfSpeech pos) {
//                            switch (pos) {
//                                case PartOfSpeech::Noun: return "noun";
//                                case PartOfSpeech::Pronoun: return "pronoun";
//                                case PartOfSpeech::Adjective: return "adjective";
//                                case PartOfSpeech::Adverb: return "adverb";
//                                case PartOfSpeech::Verb: return "verb";
//                                case PartOfSpeech::Preposition: return "preposition";
//                                case PartOfSpeech::Conjunction: return "conjunction";
//                                case PartOfSpeech::Interjection: return "interjection";
//                                default: return "";
//                            }
//                        }(m_words[i].m_pos) << ") ";
//                    }
//                    std::cout << m_words[i].m_definition << std::endl;
                }
                found = true;
                if (!g_settings.m_show_all) {
                    break;
                }
            }
        }
        if (!found) {
            std::cout << "Word '" << word << "' was not found in the dictionary." << std::endl;
        }*/
    }

    ostream& operator<<(ostream &os, const Dictionary &dic) {
        for (size_t i = 0; i < dic.m_size; ++i) {
//            os << dic.m_words;
        }
        return os;
    }

    string Dictionary::transferPTypeToString(const PartOfSpeech pos) const {
        switch(pos) {
            case PartOfSpeech::Noun:
                return "Noun";
            case PartOfSpeech::Pronoun:
                return "Pronoun";
            case PartOfSpeech::Adjective:
                return "Adjective";
            case PartOfSpeech::Adverb:
                return "Adverb";
            case PartOfSpeech::Verb:
                return "Verb";
            case PartOfSpeech::Preposition:
                return "Preposition";
            case PartOfSpeech::Conjunction:
                return "Conjunction";
            case PartOfSpeech::Interjection:
                return "Interjection";
            case PartOfSpeech::Unknown:
            default:
                return "Unknown";
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

/*    void Dictionary::resize() {

        Word* newWords = new Word[m_size + 1];
        for (size_t i = 0; i < m_size; ++i) {
            newWords[i] = m_words[i];
        }
        delete[] m_words;
        m_words = newWords;
    }*/
}