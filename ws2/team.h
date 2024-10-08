//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-10-07 Creat this file
//Done on

//

#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H
#include <string>
#include "character.h"
using namespace std;

namespace seneca{
    class Team{
        string m_name{};
        Character** m_members{};
        size_t m_size{};//team size
    public:
        Team() = default;
        Team(const char* name);
        //rule of five
        //copy constructor
        Team(const Team& src);
        //copy assignment
        Team& operator=(const Team& src);
        //move constructor
        Team(Team&& src) noexcept;
        //move assignment
        Team& operator=(Team&& src) noexcept;
        //destructor
        ~Team();

        void addMember(const Character* c);
        void removeMember(const std::string& c);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };
}
#endif //SENECA_TEAM_H
