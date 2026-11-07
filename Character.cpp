#include "Character.h"
#include <cstdlib>

/* ========== Character Class ========== */

// Character constructor provided
Character::Character(const std::string& name, int hp, int attack, int defense)
    : name(name), max_hp(hp), current_hp(hp), attack(attack),
      defense(defense), alive(true) {
}

Character::~Character() {
}

int Character::calculateDamage() const {
    int bonusDamage = rand()%5;
    return attack + bonusDamage;
}

void Character::takeDamage(int damage) {
    // "Name takes X damage! (Y/Z HP)"
    int damageTaken = damage - defense;
    if(damageTaken < 0){
        damageTaken = 0;
    }
    current_hp = current_hp - damageTaken;

    if(current_hp <= 0){
        current_hp = 0;
        alive = false;
    }

    std::cout << name << " takes " << damageTaken <<  " damage! (" << current_hp << "/" << max_hp << " HP)\n";
}

void Character::heal(int amount) {
    // "Name heals X HP! (Y/Z HP)"
    int old_hp = current_hp;
    current_hp += amount;

    if(current_hp > max_hp){
        current_hp = max_hp;
    }
    int heals = current_hp - old_hp;

    std::cout << name << " heals " << heals << " HP! (" << current_hp << "/" << max_hp << " HP)\n";
}

void Character::displayStats() const {
    // "Name [HP: current/max]"
    std::cout << name << " [HP: " << current_hp << "/" << max_hp << "]\n";
}

// Operator overloading for printing - provided 
std::ostream& operator<<(std::ostream& os, const Character& character) {
    os << character.getName() << " [HP: " << character.getCurrentHP()
       << "/" << character.getMaxHP() << "]";
    return os;
}
