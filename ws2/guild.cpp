//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-10-07 Creat this file
//Done on

//

#include "guild.h"

using namespace seneca;
using namespace std;
namespace seneca {
    Guild::Guild(const char *name) : m_name{name} {}

    Guild::Guild(const Guild &src) {
        *this = src;
    }

    //copy assignment
    Guild &Guild::operator=(const Guild &src) {
        if (this != &src) {//self assignment check
            //delete old membersœ
            for (int i = 0; i < m_size; ++i) {
                delete m_members[i];
            }
            delete[] m_members;
            m_members = nullptr;
            //deep copy
            m_members = new Character *[src.m_size];
            for (int i = 0; i < src.m_size; ++i) {
                m_members[i] = src.m_members[i]->clone();
            }
            //shallow copy
            m_name = src.m_name;
            m_size = src.m_size;
        }
        return *this;
    }

    Guild::Guild(Guild &&src) noexcept {
        *this = std::move(src);
    }

    Guild &Guild::operator=(seneca::Guild &&src) noexcept {
        if (this != &src) {
            m_name = src.m_name;
            m_size = src.m_size;
            m_members = src.m_members;
            src.m_members = nullptr;
            src.m_size = 0;
            src.m_name = "";
        }
        return *this;
    }

    Guild::~Guild() {
        delete[] m_members;
        m_members = nullptr;
    }

//adds the character received as parameter to the guild ONLY IF it's not already in the guild. Resize the array if necessary.
// If not already in the guild, increase the max health of the character by 300 points.
    void Guild::addMember(Character *c) {
        //check if the character is already in the team or not
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c->getName()) {
                return;
            }
        }
        //if the character is not in the team, add it to the team
        Character **tmp = new Character *[m_size + 1];
        //copy the old members to the new array
        for (int i = 0; i < m_size; ++i) {
            tmp[i] = m_members[i];
        }
        //increase the max health of the character by 300 points
        c->setHealthMax(c->getHealthMax() + 300);
        c->setHealth(c->getHealthMax());
        //add the new member to the new array
        tmp[m_size] = c;
        //delete the old array
        delete[] m_members;
        m_members = tmp;
        m_size++;

    }

    void Guild::removeMember(const string &c) {
        //find the character in the team
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c) {//if found
                //every one in the guild will decrease the max health by 300 points
                m_members[i]->setHealthMax(m_members[i]->getHealthMax() - 300);
                m_members[i]->setHealth(m_members[i]->getHealthMax());

                //remove the member
                for(size_t j = i; j < m_size - 1; ++j){
                    m_members[j] = m_members[j + 1];
                }
                m_size--;
                break;
            }
        }
    }

    Character *Guild::operator[](size_t idx) const {
        if (idx < m_size) {
            return m_members[idx];
        }
        return nullptr;
    }

    void Guild::showMembers() const {
        if (m_name[0] == '\0') {
            cout << "No guild." << endl;
        } else {
            cout << "[Guild] " << m_name << endl;
            for (int i = 0; i < m_size; ++i) {
                cout << "    " << i + 1 << ": " << *m_members[i] << endl;
            }
        }
    }
}
