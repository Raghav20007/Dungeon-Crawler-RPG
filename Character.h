#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>

class Character {
protected:
    std::string name;
    int max_hp;
    int current_hp;
    int attack;
    int defense;
    bool alive;

public:
    // Constructor and virtual destructor
    Character(const std::string& name, int hp, int attack, int defense);
    virtual ~Character();

    // Virtual methods - can be overridden by derived classes
    virtual int calculateDamage() const;
    virtual void displayStats() const;

    // Non-virtual methods
    void takeDamage(int damage);
    void heal(int amount);

    // Getters
    std::string getName() const { return name; }
    int getMaxHP() const { return max_hp; }
    int getCurrentHP() const { return current_hp; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    bool isAlive() const { return alive; }

    // Setters (for leveling up)
    void setMaxHP(int hp) { max_hp = hp; }
    void setCurrentHP(int hp) { current_hp = hp; }
    void setAttack(int atk) { attack = atk; }
    void setDefense(int def) { defense = def; }

    // Operator overloading
    friend std::ostream& operator<<(std::ostream& os, const Character& character);
};

#endif
