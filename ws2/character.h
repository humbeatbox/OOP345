//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-10-07 Creat this file
//Done on

//
#ifndef SENECA_CHARACTER_H
#define SENECA_CHARACTER_H
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
namespace seneca
{
    /// <summary>
    /// Represents a playable character.
    /// </summary>
    class Character
    {
        /// <summary>
        /// The name of the character.
        /// </summary>
        std::string m_name{};
    public:
        /// <summary>
        /// Initializes a new character.
        /// </summary>
        /// <param name="name">The name of the new character.</param>
        Character(const char* name) : m_name{ name } {}

        /// <summary>
        /// Get's the name of this character.
        /// </summary>
        const std::string& getName() const { return m_name; }

        /// <summary>
        /// Returns true if this character is still alive (there is health left).
        /// </summary>
        bool isAlive() const { return getHealth() > 0; }

        /// <summary>
        /// Gets the total attack, without any enhancements done by
        /// special abilities.
        /// </summary>
        virtual int getAttackAmnt() const = 0;

        /// <summary>
        /// Gets the total defense, without any enhancements done by
        /// special abilities.
        /// </summary>
        virtual int getDefenseAmnt() const = 0;

        /// <summary>
        /// Gets the current health of the character.
        /// </summary>
        virtual int getHealth() const = 0;

        /// <summary>
        /// Sets the health of the current character to the value
        /// received as parameter.
        /// </summary>
        virtual void setHealth(int health) = 0;

        /// <summary>
        /// Gets the maximum health of this character.
        /// </summary>
        virtual int getHealthMax() const = 0;

        /// <summary>
        /// Sets the maximum health of this character and the health to
        /// the maximum value.
        /// </summary>
        /// <param name="health">the new maximum health.</param>
        virtual void setHealthMax(int health) = 0;

        /// <summary>
        /// Creates a copy of this character using the copy constructor.
        /// </summary>
        /// <returns></returns>
        virtual Character* clone() const = 0;

        /// <summary>
        /// Attacks another character using all the weapons and special
        /// abilities this character has.
        /// </summary>
        /// <param name="enemy">the adversary being attacked.</param>
        virtual void attack(Character* enemy) = 0;

        /// <summary>
        /// Take damage in the amount specified as parameter. The damage
        /// can be reduced by defense and special abilities.
        /// </summary>
        virtual void takeDamage(int dmg) = 0;
        virtual ~Character() = default;

        /// <summary>
        /// Prints to screen information about current character.
        /// </summary>
        friend std::ostream& operator<<(std::ostream& out, const Character& c)
        {
            out.setf(std::ios::left);
            out << std::setw(20) << c.m_name << "  ";
            out.unsetf(std::ios::left);

            int health = 100 * c.getHealth() / c.getHealthMax();
            out << "  Health: " << std::setw(3) << health << "% ";
            out << '(' << std::setw(4) << c.getHealth() << '/'
                << std::setw(4) << c.getHealthMax() << ')';
            out << "  Attack: "  << std::setw(4) << c.getAttackAmnt();
            out << "  Defense: " << std::setw(4) << c.getDefenseAmnt();
            return out;
        }
    };


}


#endif