//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-10-08 Creat this file
//Done on

//

#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H
#include "character.h"
using namespace std;
namespace seneca {

    template<typename T>
    class CharacterTpl : public Character {
        int m_healthMax{};
        T m_health{};
    public:
//        CharacterTpl(const char* name, int healthMax):Character(name), m_healthMax{healthMax}, m_health{healthMax}{}
        CharacterTpl(const char *name, int healthMax) : Character(name) {
            m_healthMax = healthMax;
            m_health = healthMax;
        }

        void takeDamage(int dmg) override {
            m_health -= dmg;
            if (static_cast<int>(m_health) < 0) {
                m_health = 0;
                cout << "    " << getName() << " has been defeated!" << endl;
            } else {
                cout << "    " << getName() << " took " << dmg << " damage, " << m_health << " health remaining."
                     << endl;
            }
        }

        int getHealth() const override {
            return (m_health);
        }

        int getHealthMax() const override {
            return static_cast<int>(m_healthMax);
        }

        void setHealth(int health) override {
            m_health = health;
        }

        void setHealthMax(int health) override {
            m_healthMax = health;
            m_health = health;
        }
    };
}

#endif //SENECA_CHARACTERTPL_H
