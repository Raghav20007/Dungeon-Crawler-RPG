#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

// ============================================================================
// Base Item class
// ============================================================================
class Item {
protected:
    std::string name;
    std::string description;
    std::string type;
    int value;

public:
    Item(const std::string& name, const std::string& description,
         const std::string& type, int value);
    virtual ~Item();

    // Virtual method - overridden by derived classes
    virtual void displayInfo() const;

    // Non-virtual methods
    void displayBrief() const;

    // Getters
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    std::string getType() const { return type; }
    int getValue() const { return value; }

    // Operator overloading
    friend std::ostream& operator<<(std::ostream& os, const Item& item);
};

// ============================================================================
// Weapon class - increases attack damage
// ============================================================================
class Weapon : public Item {
private:
    int damage_bonus;

public:
    Weapon(const std::string& name, const std::string& description, int damage);

    void displayInfo() const;

    int getDamageBonus() const { return damage_bonus; }
};

// ============================================================================
// Armor class - increases defense
// ============================================================================
class Armor : public Item {
private:
    int defense_bonus;

public:
    Armor(const std::string& name, const std::string& description, int defense);

    void displayInfo() const;

    int getDefenseBonus() const { return defense_bonus; }
};

// ============================================================================
// Consumable class - healing items
// ============================================================================
class Consumable : public Item {
private:
    int healing_amount;
    bool used;

public:
    Consumable(const std::string& name, const std::string& description, int healing);

    void displayInfo() const;
    void use();

    int getHealingAmount() const { return healing_amount; }
    bool isUsed() const { return used; }
};

#endif
