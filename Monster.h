#ifndef MONSTER_H
#define MONSTER_H

#include "Character.h"
#include "Item.h"
#include <vector>
#include <string>

// ============================================================================
// Base Monster class
// ============================================================================
class Monster : public Character {
protected:
    int experience_reward;
    int gold_reward;
    std::vector<Item*> loot_table;

public:
    Monster(const std::string& name, int hp, int attack, int defense,
            int exp_reward, int gold_reward);
    ~Monster();

    // Override virtual methods
    void displayStats() const;
    virtual std::string getAttackMessage() const;

    // Loot management
    void addLoot(Item* item);
    std::vector<Item*> dropLoot();

    // Getters
    int getExperienceReward() const { return experience_reward; }
    int getGoldReward() const { return gold_reward; }
};

// ============================================================================
// Goblin - weak but common enemy
// ============================================================================
class Goblin : public Monster {
public:
    Goblin();
    std::string getAttackMessage() const;
};

// ============================================================================
// Skeleton - undead warrior
// ============================================================================
class Skeleton : public Monster {
public:
    Skeleton();
    std::string getAttackMessage() const;
};

// ============================================================================
// Dragon - boss enemy with bonus fire damage
// ============================================================================
class Dragon : public Monster {
public:
    Dragon();
    std::string getAttackMessage() const;
    int calculateDamage() const;  // Override for bonus fire damage
};

#endif
