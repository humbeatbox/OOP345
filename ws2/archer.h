//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-10-07 Creat this file
//Done on

//

#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H
#include "health.h"
#include "character.h"

using namespace std;

namespace seneca{
    template <typename Weapon_t>
    class Archer : public CharacterTpl<SuperHealth> {
        int m_baseDefense{};
        int m_baseAttack{};
        Weapon_t m_weapon{};
    public:
        Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon):CharacterTpl<SuperHealth>(name, healthMax), m_baseAttack{baseAttack}, m_baseDefense{baseDefense}, m_weapon{weapon} {}

        //copy constructor for clone
        Archer(const Archer& src):CharacterTpl<SuperHealth>(src){
            m_baseDefense = src.m_baseDefense;
            m_baseAttack = src.m_baseAttack;
            m_weapon = src.m_weapon;
        }

        int getAttackAmnt() const override{
            return (1.3 * m_baseAttack);
        }
        int getDefenseAmnt() const override{
            return (1.2 * m_baseDefense);
        }
        Character* clone() const override{
            return new Archer(*this);
        }
        void attack(Character* enemy) override{
            cout << this->getName() << " is attacking " << enemy->getName() << "." << endl;
            int myDamage = getAttackAmnt();
            cout << "Archer deals " << myDamage << " ranged damage!" << endl;
        }

        void takeDamage(int dmg) override{
            cout << this->getName() << " is attacked for " << dmg << " damage." << endl;
            cout << "Archer has a defense of " << m_baseDefense << ". Reducing damage received." << endl;
            dmg -= m_baseDefense;
            if (dmg < 0) {
                dmg = 0;
            }
            CharacterTpl<SuperHealth>::takeDamage(dmg);
        }
    };
}
#endif //SENECA_ARCHER_H
