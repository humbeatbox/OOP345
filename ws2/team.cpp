//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-10-07 Creat this file
//Done on

//

#include "team.h"
using namespace std;
using namespace seneca;
namespace seneca{
    Team::Team(const char* name):m_name{name}{}
    //copy constructor
    Team::Team(const Team &src) {
        *this = src;
    }
    //copy assignment
    Team& Team::operator=(const Team& src){
        if(this != &src){

            //TODO: check what if team members is 0???
            //delete old members
            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }
            m_name = src.m_name;
            m_size = src.m_size;
            delete[] m_members;
            m_members = nullptr;

            //copy new members
            m_members = new Character*[m_size];
            for(size_t i = 0; i < m_size; ++i){
                m_members[i] = src.m_members[i]->clone();
            }
        }
        return *this;
    }
    //move constructor
    Team::Team(Team&& src) noexcept{
        *this = std::move(src);
    }
    //move assignment
    Team& Team::operator=(Team&& src) noexcept{
        if(this != &src){
            //move old members to new team
            m_name = src.m_name;
            m_size = src.m_size;
            m_members = src.m_members;
            //delete old members
            src.m_members = nullptr;
            src.m_size = 0;
            src.m_name = "";
        }
        return *this;
    }
    //destructor
    Team::~Team(){
        //delete all members
        for(size_t i = 0; i < m_size; ++i){
            delete m_members[i];
        }
        delete[] m_members;
        m_members = nullptr;
    }

    //adds the character received as parameter to the team ONLY IF the team doesn't have a character with the same name.
    // Resize the array if necessary.
    // Use the Character::clone() function to make a copy of the parameter.
    void Team::addMember(const Character* c){
        //check if the team has a character with the same name
        for(size_t i = 0; i < m_size; ++i){
            if(m_members[i]->getName() == c->getName()){
                return;
            }
        }
        //resize the array
        Character** temp = new Character*[m_size + 1];
        for(size_t i = 0; i < m_size; ++i){
            temp[i] = m_members[i];
        }

        temp[m_size] = c->clone();
        delete[] m_members;
        m_members = temp;
        m_size++;
    }

//searches the team for a character with the name received as parameter and removes it from the team.
    void Team::removeMember(const std::string& c){
        size_t tmpIndex{};
        for(size_t i = 0; i < m_size; ++i){
            if(m_members[i]->getName() == c){//if found
                tmpIndex = i;
                delete m_members[i];//remove the member
                m_members[i] = nullptr;
                break;
            }
        }
        //if the character is not in the team, return
        if (tmpIndex == m_size) {
            return;
        }
        //resize the array
        Character** temp = new Character*[m_size - 1];
        for(size_t i = 0; i < tmpIndex; ++i){
            temp[i] = m_members[i];
        }
        for(size_t i = tmpIndex; i < m_size - 1; ++i){
            temp[i] = m_members[i + 1];
        }
        delete[] m_members;
        m_members = temp;
        m_size--;//decrease the size
    }

    // returns the character ar the index specified as parameter, or null if the index is out of bounds.
    Character* Team::operator[](size_t idx) const{
        if(idx < m_size){
            return m_members[idx];
        }
        return nullptr;
    }

    //prints to screen the content of current object in the format:
    /*[Team] TEAM_NAME<endl>
    1: FIRST_CHARACTER<endl>
    2: SECOND_CHARACTER<endl>
    3: THIRD_CHARACTER<endl>
    ...*/
    void Team::showMembers() const{
        if(m_size == 0){
            cout << "No team." << endl;
        }else{
            cout << "[Team] " << m_name << endl;
            for(size_t i = 0; i < m_size; ++i){
                cout << "    " << i + 1 << ": " << *m_members[i] << endl;
            }
        }
    }

}