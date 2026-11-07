#include "Monster.h"
#include <iostream>

/* ========== Base Monster Class ========== */

// Monster Constructor - provided
Monster::Monster(const std::string& name, int hp, int attack, int defense,
                 int exp_reward, int gold_reward)
    : Character(name, hp, attack, defense),
      experience_reward(exp_reward), gold_reward(gold_reward) {
}

Monster::~Monster() {
    for(int i = 0; i < (int)loot_table.size(); i++){
        delete loot_table[i];
    }
    loot_table.clear();
}

void Monster::displayStats() const {
    // "MonsterName [HP: current/max]"
    std::cout << name << " [HP: " << current_hp << "/" << max_hp << "]\n";
}

void Monster::addLoot(Item* item) {
    if(item != NULL){
        loot_table.push_back(item);
    }
}

std::vector<Item*> Monster::dropLoot() {
    std::vector<Item*> empty = loot_table;
    loot_table.clear();
    return empty;
}

std::string Monster::getAttackMessage() const {

    return name + " attacks!";
}

/* ========== Goblin ========== */

Goblin::Goblin()
    : Monster("Goblin", 30, 5, 2, 10, 5) {
    Consumable* smallPotion = new Consumable("Small Potion", "Restores 15 HP", 15);
    addLoot(smallPotion);
}

std::string Goblin::getAttackMessage() const {
    return "The goblin swipes at you with its rusty dagger!";
}

/* ========== Skeleton ========== */

Skeleton::Skeleton()
    : Monster("Skeleton", 40, 8, 4, 20, 10) {
    Weapon* goodWeapon = new Weapon("Sharp Iron Sword", "Deals +10 Attack Bonus!", 10);
    addLoot(goodWeapon);
}

std::string Skeleton::getAttackMessage() const {
    return "The skeleton rattles its bones and slashes with a sword!";
}

/* ========== Dragon ========== */

Dragon::Dragon()
    : Monster("Dragon", 80, 15, 5, 100, 50) {
        Weapon* greatWeapon = new Weapon("Sparkling Diamond Sword", "Deals +25 Attack Bonus", 25);
        Consumable* largePotion = new Consumable("Large Potion", "Restores 50 HP", 50);
        Armor* greatArmor = new Armor("Obsidian Chestplate and Helmet", "Increases Defense by 30", 30);
        addLoot(greatArmor);
        addLoot(greatWeapon);
        addLoot(largePotion);


}

std::string Dragon::getAttackMessage() const {
    return "The dragon breathes fire at you!";
}

int Dragon::calculateDamage() const {
    return 5 + Character::calculateDamage();
}
