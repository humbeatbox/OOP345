//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-10-07 Creat this file
//Done on

//

#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H
#include "characterTpl.h"
#include "abilities.h"
#include "weapons.h"

using namespace std;
using namespace seneca;
namespace seneca{
    template<typename T, typename FirstAbility_t,typename SecondAbility_t>
    class Rogue : public CharacterTpl<T> {
        int m_baseDefense{};
        int m_baseAttack{};
        FirstAbility_t m_firstAbility{};
        SecondAbility_t m_secondAbility{};
        seneca::Dagger m_weapon{};
    public:
        Rogue(const char* name, int healthMax, int baseAttack, int baseDefense):CharacterTpl<T>(name, healthMax), m_baseAttack{baseAttack}, m_baseDefense{baseDefense} {}

        //TODO: copy constructor for clone
        Rogue(const Rogue& src):CharacterTpl<T>(src){
            m_baseDefense = src.m_baseDefense;
            m_baseAttack = src.m_baseAttack;
            m_firstAbility = src.m_firstAbility;
            m_secondAbility = src.m_secondAbility;
            m_weapon = src.m_weapon;
        }

        int getAttackAmnt() const override{
            return (m_baseAttack + 2 * (m_weapon));
            //TODO weapon damage
        }

        int getDefenseAmnt() const override{
            return ((m_baseDefense));
            //TODO weapon damage
        }

        Character* clone() const override{
            return new Rogue(*this);
        }

        void attack(Character* enemy) override{
            cout << this->getName() << " is attacking " << enemy->getName() << "." << endl;
            m_firstAbility.useAbility(this);
            m_secondAbility.useAbility(this);
            int myDamage = getAttackAmnt();
            m_firstAbility.transformDamageDealt(myDamage);
            m_secondAbility.transformDamageDealt(myDamage);
            cout << "Rogue deals " << myDamage << " melee damage!" << endl;


            enemy->takeDamage(myDamage);
        }
        void takeDamage(int dmg)override{
            cout << this->getName() << " is attacked for " << dmg << " damage." << endl;
            cout << "Rogue has a defense of " << m_baseDefense << ". Reducing damage received." << endl;

            dmg -= m_baseDefense;
            if (dmg < 0) {
                dmg = 0;
            }
                m_firstAbility.transformDamageReceived(dmg);
                m_secondAbility.transformDamageReceived(dmg);
            CharacterTpl<T>::takeDamage(dmg);
        }
    };


}


#endif //SENECA_ROGUE_H
