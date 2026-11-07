#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Item.h"
#include <vector>
#include <string>

class Player : public Character {
private:
    int level;
    int experience;
    int gold;
    std::vector<Item*> inventory;
    Item* equipped_weapon;
    Item* equipped_armor;

public:
    // Constructor and destructor
    Player(const std::string& name);
    ~Player();

    // Override virtual methods from Character
    void displayStats() const;
    int calculateDamage() const;

    // Inventory management
    void addItem(Item* item);
    void removeItem(const std::string& item_name);
    void displayInventory() const;
    bool hasItem(const std::string& item_name) const;
    Item* getItem(const std::string& item_name);

    // Equipment
    void equipWeapon(const std::string& weapon_name);
    void equipArmor(const std::string& armor_name);
    void unequipWeapon();
    void unequipArmor();

    // Item usage
    void useItem(const std::string& item_name);

    // Experience and leveling
    void gainExperience(int exp);
    void levelUp();

    // Gold management
    void addGold(int amount) { gold += amount; std::cout << "Got " << amount << " gold!" << std::endl; }
    int getGold() const { return gold; }

    // Getters
    int getLevel() const { return level; }
    int getExperience() const { return experience; }

    // Save/Load
    void saveToFile(std::ostream& out) const;
    void loadFromFile(std::istream& in);
};

#endif
