//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-10-07 Creat this file
//Done on

//
#include "characterTpl.h"
#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

using namespace std;
namespace seneca{
    template <typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T>{
        int m_baseAttack{};
        int m_baseDefense{};
        Ability_t m_ability{};
        Weapon_t m_weapon[2]{};
    public:
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon): CharacterTpl<T>(name, healthMax), m_baseAttack{baseAttack}, m_baseDefense{baseDefense}, m_weapon{primaryWeapon, secondaryWeapon} {}

        int getAttackAmnt() const override{
            return m_baseAttack + (static_cast<int>(m_weapon[0]) * 0.5) + (static_cast<int>(m_weapon[1]) * 0.5);
        }

        int getDefenseAmnt() const override{
            return m_baseDefense;
        }

        Character* clone() const override{
            return new Barbarian(*this);
        }

        void attack(Character* enemy) override{
            cout << this->getName() << " is attacking " << enemy->getName() << "." << endl;
            m_ability.useAbility(this);
            int myDamage = getAttackAmnt();
            //TODO: check this part
            m_ability.transformDamageDealt(myDamage);
            cout << "    Barbarian deals " << myDamage << " melee damage!" <<endl;
            enemy->takeDamage(myDamage);
        }
        void takeDamage(int dmg)override{
            cout << this->getName() << " is attacked for " << dmg << " damage." << endl;
            cout << "    Barbarian has a defense of " << m_baseDefense << ". Reducing damage received." << endl;

            dmg -= m_baseDefense;
            if (dmg < 0) {
                dmg = 0;
            }
            m_ability.transformDamageReceived(dmg);
            CharacterTpl<T>::takeDamage(dmg);
        }
    };
}
#endif //SENECA_BARBARIAN_H
