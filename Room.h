#ifndef ROOM_H
#define ROOM_H

#include "Monster.h"
#include "Item.h"
#include <string>
#include <map>
#include <vector>

class Room {
private:
    std::string name;
    std::string description;
    bool visited;
    Monster* monster;
    std::vector<Item*> items;
    std::map<std::string, Room*> exits;

public:
    Room(const std::string& name, const std::string& description);
    ~Room();

    // Display
    void display() const;
    void displayExits() const;
    void displayItems() const;

    // Navigation
    void addExit(const std::string& direction, Room* room);
    Room* getExit(const std::string& direction) const;
    bool hasExit(const std::string& direction) const;

    // Monster management
    void setMonster(Monster* m) { monster = m; }
    Monster* getMonster() const { return monster; }
    bool hasMonster() const { return monster != NULL; }
    void clearMonster();

    // Item management
    void addItem(Item* item);
    void removeItem(const std::string& item_name);
    Item* getItem(const std::string& item_name);
    bool hasItems() const { return !items.empty(); }

    // State
    void markVisited() { visited = true; }
    bool isVisited() const { return visited; }

    // Getters
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
};

#endif
