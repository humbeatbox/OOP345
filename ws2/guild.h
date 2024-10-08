//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-10-07 Creat this file
//Done on

//

#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H
#include <string>
#include "character.h"
using namespace std;
/*
 * Design and code a class named Guild that manages a dynamically allocated collection of characters in the form of an array.
 * Because Character is abstract and cannot be instantiated, this class should work with an array of pointers to Character.
 * At minimum, this class should store the address of the array and a string with the name of this team;
 * add any other private members and any public special operations that your design requires.
 * The Guild is in aggregation relation with Character.
 * All guild members receive extra 300 health points on joining;
 * these points are removed when the character leaves the guild.
 * */
namespace seneca{
    class Guild{
        string m_name{};
        Character** m_members{};
        size_t m_size{};//team size
    public:
        Guild() = default;
        Guild(const char* name);
        //rule of five
        //copy constructor
        Guild(const Guild& src);
        //copy assignment
        Guild& operator=(const Guild& src);
        //move constructor
        Guild(Guild&& src) noexcept;
        //move assignment
        Guild& operator=(Guild&& src) noexcept;
        //destructor
        ~Guild();

        void addMember(Character* c);
        void removeMember(const std::string& c);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };
}
#endif //SENECA_GUILD_H
