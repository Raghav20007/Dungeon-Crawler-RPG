#include "Player.h"
#include <iostream>
#include <cctype>

// Helper function for case-insensitive string comparison
// Provided for you - do not modify
static bool iequals(const std::string& a, const std::string& b) {
    if (a.length() != b.length()) return false;
    for (int i = 0; i < (int)a.length(); i++) {
        if (tolower(a[i]) != tolower(b[i])) return false;
    }
    return true;
}

/* ========== Player Class ========== */

// Constructor - provided for you
Player::Player(const std::string& name)
    : Character(name, 100, 10, 5),
      level(1), experience(0), gold(0),
      equipped_weapon(NULL), equipped_armor(NULL) {
}

Player::~Player() {
    for(int i = 0; i < (int)inventory.size(); i++){
        delete inventory[i];
    }
    inventory.clear();
}

void Player::displayStats() const {
    /*
===== PlayerName =====
Level: 1
HP: 100/100
Attack: 10 (+5 from weapon)
Defense: 5 (+3 from armor)
Gold: 0
Experience: 0
=====================
*/
    std::cout << "===== " << name <<  " =====\n" << "Level: " << level << "\n";
    std::cout << "HP: " << current_hp << "/" << max_hp << "\n";
    if (equipped_weapon != NULL){
        Weapon *currentWeapon = (Weapon*)equipped_weapon;
        int attackTotal = attack + currentWeapon->getDamageBonus();
        std::cout << "Attack: " << attackTotal << " (+" << currentWeapon->getDamageBonus() << " from weapon)\n";
    } else {
        std::cout << "Attack: " << attack << "\n";
    }

    if(equipped_armor != NULL){
        Armor *currentArmor = (Armor*)equipped_armor;
        int defenseTotal = defense + currentArmor->getDefenseBonus();
        std::cout << "Defense: " << defenseTotal << " (+" << currentArmor->getDefenseBonus() << " from armor)\n";
    } else {
        std::cout << "Defense: " << defense << "\n";
    }

    std::cout << "Gold: " << gold << "\n";
    std::cout << "Experience: " << experience << "\n";
    std::cout << "=====================\n";
}

int Player::calculateDamage() const {
    // TODO: Implement this function
    int attackDamage = Character::calculateDamage();
    if(equipped_weapon != NULL){
        Weapon *currentWeapon = (Weapon*)equipped_weapon;
        int totalAttack = attackDamage + currentWeapon->getDamageBonus();
        return totalAttack;
    }

    return attackDamage;
}

void Player::addItem(Item* item) {
    // "Picked up: ItemName"

    inventory.push_back(item);
    std::cout << "Picked up: " << item->getName() << "\n";
}

void Player::removeItem(const std::string& item_name) {
    //"Removed: ItemName"
    //"Item not found: ItemName"

    for(int i = 0; i < inventory.size(); i++){

        if(iequals(inventory[i]->getName(), item_name)){
            std::string currentName = inventory[i]->getName();
            if(equipped_armor == inventory[i]){
                equipped_armor = NULL;
            }
            if(equipped_weapon == inventory[i]){
                equipped_weapon = NULL;
            }

            delete inventory[i];
            inventory.erase(inventory.begin() + i);
            std::cout << "Removed: " << currentName << "\n";
            return;
        }
    }
    std::cout << "Item not found: " << item_name << "\n";
}

void Player::displayInventory() const {
    /*Print header: "----- Inventory -----"
If inventory is empty: print "Empty"
Otherwise: print each item as "- ItemName (ItemType)"
Print footer: "--------------------" */

    std::cout << "----- Inventory -----\n";
    if(inventory.empty()){
        std::cout << "Empty\n";
    } else {
        for(int i = 0; i < (int)inventory.size(); i++){
            std::cout << "- " << inventory[i]->getName() << " (" << inventory[i]->getType() << ")\n";
        }
    }
    std::cout << "--------------------\n";
}

bool Player::hasItem(const std::string& item_name) const {
    // TODO: Implement this function
    for(int i = 0; i < (int)inventory.size(); i++){
        if(iequals(inventory[i]->getName(), item_name)){
            return true;
        }
    }

    return false;
}

Item* Player::getItem(const std::string& item_name) {
    // TODO: Implement this function
    for(int i = 0; i < (int)inventory.size(); i++){
        if(iequals(inventory[i]->getName(), item_name)){
            return inventory[i];
        }
    }
    return NULL;
}

void Player::equipWeapon(const std::string& weapon_name) {
    // "Attack bonus: +X"
    Item* item = Player::getItem(weapon_name);

    if(item == NULL){
        std::cout << "You don't have that item!\n";
        return;
    }

    if(item->getType() != "Weapon"){
        std::cout << "That's not a weapon!\n";
        return;
    }

    if(equipped_weapon != NULL){
        std::cout << "Unequipping " << equipped_weapon->getName() << "\n";
    }
    equipped_weapon = item;
    Weapon* weapon = (Weapon*)item;
    std::cout << "Equipped " << equipped_weapon->getName() << "!\n";
    std::cout << "Attack bonus: +" << weapon->getDamageBonus() << "\n";
}

void Player::equipArmor(const std::string& armor_name) {
    // TODO: Implement this function
    Item* item = Player::getItem(armor_name);

    if(item == NULL){
        std::cout << "You don't have that item!\n";
        return;
    }

    if(item->getType() != "Armor"){
        std::cout << "That's not armor!\n";
        return;
    }

    if(equipped_armor != NULL){
        std::cout << "Unequipping " << equipped_armor->getName() << "\n";
    }
    equipped_armor = item;
    Armor* armor = (Armor*)item;
    std::cout << "Equipped " << equipped_armor->getName() << "!\n";
    std::cout << "Defense bonus: +" << armor->getDefenseBonus() << "\n";
}

void Player::unequipWeapon() {
    // If a weapon is equipped: print "Unequipped WeaponName" and set equipped_weapon to NULL
    //If no weapon equipped: print "No weapon equipped!"

    if(equipped_weapon == NULL){
        std::cout << "No weapon equipped!\n";
        return;
    }
    std::cout << "Unequipped " << equipped_weapon->getName() << "\n";
    equipped_weapon = NULL;
}

void Player::unequipArmor() {
    // If armor is equipped: print "Unequipped ArmorName" and set equipped_armor to NULL
    //If no armor equipped: print "No armor equipped!"

    if(equipped_armor == NULL){
        std::cout << "No armor equipped!\n";
        return;
    }
    std::cout << "Unequipped " << equipped_armor->getName() << "\n";
    equipped_armor = NULL;
}

void Player::useItem(const std::string& item_name) {
    // Find item in inventory using getItem()
    //If found and type is "Consumable": call heal() with the item's value, then call removeItem() to consume it
    //Otherwise: print "Cannot use ItemName"
    Item* item = Player::getItem(item_name);
    if(item == NULL){
        std::cout << "Cannot use " << item_name << "\n";
        return;
    }
    Consumable* healing = (Consumable*) item;
    
    if(item->getType() == "Consumable"){
        heal(healing->getHealingAmount());
        healing->use();
        removeItem(item_name);
    } else {
        std::cout << "Cannot use " << item_name << "\n";
    }

}

void Player::gainExperience(int exp) {
    // Add exp to experience
    //Print: "Gained X experience!"
    //If experience >= level * 100: call levelUp()

    experience += exp;
    std::cout << "Gained " << exp << " experience!\n";

    if(experience >= level * 100){
        levelUp();
    }
}

void Player::levelUp() {
    /*Increment level
Reset experience to 0
Increase max_hp by 10
Set current_hp to max_hp (full heal)
Increase attack by 2
Increase defense by 1
Print "*** LEVEL UP! ***" followed by "You are now level X!"
Call displayStats() to show updated stats */ 
    level++;
    experience = 0;
    max_hp += 10;
    current_hp = max_hp;
    attack += 2;
    defense += 1;
    std::cout << "*** LEVEL UP! ***\n";
    std::cout << "You are now level " << level << "!\n";
    displayStats();
}

// Save/Load - provided for you
void Player::saveToFile(std::ostream& out) const {
    out << name << std::endl;
    out << max_hp << " " << current_hp << std::endl;
    out << attack << " " << defense << std::endl;
    out << level << " " << experience << " " << gold << std::endl;
}

void Player::loadFromFile(std::istream& in) {
    std::getline(in, name);
    in >> max_hp >> current_hp;
    in >> attack >> defense;
    in >> level >> experience >> gold;
    alive = (current_hp > 0);
}
