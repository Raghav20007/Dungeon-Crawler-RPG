#include "Player.h"
#include <iostream>
#include <cctype>

// Helper function for case-insensitive string comparison - Provided
static bool iequals(const std::string& a, const std::string& b) {
    if (a.length() != b.length()) return false;
    for (int i = 0; i < (int)a.length(); i++) {
        if (tolower(a[i]) != tolower(b[i])) return false;
    }
    return true;
}

/* ========== Player Class ========== */

//Player Constructor - provided
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
void Player::displayStats() const {

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
    int attackDamage = Character::calculateDamage();
    if(equipped_weapon != NULL){
        Weapon *currentWeapon = (Weapon*)equipped_weapon;
        int totalAttack = attackDamage + currentWeapon->getDamageBonus();
        return totalAttack;
    }

    return attackDamage;
}

// "Picked up: ItemName"
void Player::addItem(Item* item) {

    inventory.push_back(item);
    std::cout << "Picked up: " << item->getName() << "\n";
}

//"Removed: ItemName"
//"Item not found: ItemName"
void Player::removeItem(const std::string& item_name) {

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

/*
    Print header: "----- Inventory -----"
    If inventory is empty: print "Empty"
    Otherwise: print each item as "- ItemName (ItemType)"
    Print footer: "--------------------" 
*/
void Player::displayInventory() const {
    
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
    for(int i = 0; i < (int)inventory.size(); i++){
        if(iequals(inventory[i]->getName(), item_name)){
            return true;
        }
    }

    return false;
}

Item* Player::getItem(const std::string& item_name) {
    for(int i = 0; i < (int)inventory.size(); i++){
        if(iequals(inventory[i]->getName(), item_name)){
            return inventory[i];
        }
    }
    return NULL;
}

// "Attack bonus: +X"
void Player::equipWeapon(const std::string& weapon_name) {

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


    // If a weapon is equipped: print "Unequipped WeaponName" and set equipped_weapon to NULL
    //If no weapon equipped: print "No weapon equipped!"
void Player::unequipWeapon() {
    if(equipped_weapon == NULL){
        std::cout << "No weapon equipped!\n";
        return;
    }
    std::cout << "Unequipped " << equipped_weapon->getName() << "\n";
    equipped_weapon = NULL;
}

    // If armor is equipped: print "Unequipped ArmorName" and set equipped_armor to NULL
    //If no armor equipped: print "No armor equipped!"
void Player::unequipArmor() {
    if(equipped_armor == NULL){
        std::cout << "No armor equipped!\n";
        return;
    }
    std::cout << "Unequipped " << equipped_armor->getName() << "\n";
    equipped_armor = NULL;
}

    // Find item in inventory using getItem()
    //If found and type is "Consumable": call heal() with the item's value, then call removeItem() to consume it
    //Otherwise: print "Cannot use ItemName"
void Player::useItem(const std::string& item_name) {
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

    // Add exp to experience
    //Print: "Gained X experience!"
    //If experience >= level * 100: call levelUp()
void Player::gainExperience(int exp) {
    experience += exp;
    std::cout << "Gained " << exp << " experience!\n";

    if(experience >= level * 100){
        levelUp();
    }
}

/*
    Increment level
    Reset experience to 0
    Increase max_hp by 10
    Set current_hp to max_hp (full heal)
    Increase attack by 2
    Increase defense by 1
    Print "*** LEVEL UP! ***" followed by "You are now level X!"
    Call displayStats() to show updated stats 
*/ 
void Player::levelUp() {
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
