//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-09-17 Creat this file
//Done on

//

#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H
#include <string>
#include <ostream>
namespace seneca{
    enum class PartOfSpeech
    {
        Unknown,
        Noun,
        Pronoun,
        Adjective,
        Adverb,
        Verb,
        Preposition,
        Conjunction,
        Interjection,
    };
    struct Word
    {
        std::string m_word{};
        std::string m_definition{};
        PartOfSpeech m_pos = PartOfSpeech::Unknown;
    };

    class Dictionary{
        Word* m_words{};
        size_t m_size{};
    public:
        Dictionary();
        Dictionary(const char* filename);
        ~Dictionary();

        Dictionary(const Dictionary&);
        Dictionary& operator=(const Dictionary&);
        Dictionary(Dictionary&&) noexcept;
        Dictionary& operator=(Dictionary&&) noexcept;

        void searchWord(const char* word) const;
        PartOfSpeech transfertoPType(const std::string)const;
        std::string transferPTypeToString(const PartOfSpeech)const;

    };

}
#endif //SENECA_DICTIONARY_H
