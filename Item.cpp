#include "Item.h"

/* ========== Base Item Class ========== */

// Item Constructor - provided
Item::Item(const std::string& name, const std::string& description,
           const std::string& type, int value)
    : name(name), description(description), type(type), value(value) {
}

Item::~Item() {
}

void Item::displayInfo() const {
// [ITEM] ItemName, Description text, Value: X
  std::cout << "[ITEM] " << name << "\n" << description << "\n" << "Value: " << value << "\n";
}

void Item::displayBrief() const {
    //  "Iron Sword (Weapon)"
    std::cout << name << " (" << type << ")\n";
}

/* ========== Weapon Class ========== */

//Weapon Constructor - provided 
Weapon::Weapon(const std::string& name, const std::string& description, int damage)
    : Item(name, description, "Weapon", damage), damage_bonus(damage) {
}

void Weapon::displayInfo() const {
    // [WEAPON] WeaponName, Description text, Damage Bonus: +X
  std::cout << "[WEAPON] " << name << "\n" << description << "\n" << "Damage Bonus: +" << damage_bonus << "\n";
}

/* ========== Armor Class ========== */

// Armor Constructor - provided
Armor::Armor(const std::string& name, const std::string& description, int defense)
    : Item(name, description, "Armor", defense), defense_bonus(defense) {
}

void Armor::displayInfo() const {
    // [ARMOR] ArmorName, Description text, Defense Bonus: +X
  std::cout << "[ARMOR] " << name << "\n" << description << "\n" << "Defense Bonus: +" << defense_bonus << "\n";

}

/* ========== Consumable Class ========== */

// Consumable Constructor - provided
Consumable::Consumable(const std::string& name, const std::string& description,
                       int healing)
    : Item(name, description, "Consumable", healing),
      healing_amount(healing), used(false) {
}

void Consumable::displayInfo() const {
    // [CONSUMABLE] ConsumableName, Description text, Restores: X HP
  std::cout << "[CONSUMABLE] " << name << "\n" << description << "\n" << "Restores: " << healing_amount << " HP\n";

}

void Consumable::use() {
    //"ItemName has already been used!"
    //"Used ItemName! Restored X HP."
    if(used == true ){
        std::cout << name << " has already been used!\n";
    } else {
        std::cout << "Used " << name << "! Restored " << healing_amount << " HP.\n";
        used = true;
    }
    
}

// Operator overloading for printing - Provided
std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << item.getName() << " (" << item.getType() << ")";
    return os;
}
