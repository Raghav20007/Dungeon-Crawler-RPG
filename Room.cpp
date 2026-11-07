#include "Room.h"
#include <iostream>
#include <cctype>

// Helper function for case-insensitive string comparison
static bool iequals(const std::string& a, const std::string& b) {
    if (a.length() != b.length()) {
        return false;
    }
    for (int i = 0; i < (int)a.length(); i++) {
        if (tolower(a[i]) != tolower(b[i])) return false;
    }
    return true;
}

Room::Room(const std::string& name, const std::string& description)
    : name(name), description(description), visited(false), monster(NULL) {
}

Room::~Room() {
    // Clean up monster if still present
    if (monster) {
        delete monster;
    }
    
    // Clean up items
    for (int i = 0; i < (int)items.size(); i++) {
        delete items[i];
    }
    items.clear();
    
    // Note: We don't delete connected rooms - they're managed by Game class
}

// Display room information
void Room::display() const {
    std::cout << "\n========================================" << std::endl;
    std::cout << name << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << description << std::endl;
    
    if (hasMonster()) {
        std::cout << "\nA " << monster->getName() << " blocks your path!" << std::endl;
    }
    
    if (hasItems()) {
        std::cout << "\nItems here:" << std::endl;
        displayItems();
    }
    
    std::cout << std::endl;
    displayExits();
    std::cout << "========================================\n" << std::endl;
}

// Display available exits
void Room::displayExits() const {
    std::cout << "\nExits: ";
    if (exits.empty()) {
        std::cout << "None (you're trapped!)" << std::endl;
    } else {
        bool first = true;
        for (std::map<std::string, Room*>::const_iterator it = exits.begin(); it != exits.end(); it++) {
            if (!first) std::cout << ", ";
            std::cout << it->first;
            first = false;
        }
        std::cout << std::endl;
    }
}

// Add an exit to another room
void Room::addExit(const std::string& direction, Room* room) {
    if (room) {
        exits[direction] = room;
    }
}

// Get the room in a given direction
Room* Room::getExit(const std::string& direction) const {
    std::map<std::string, Room*>::const_iterator it = exits.find(direction);
    if (it != exits.end()) {
        return it->second;
    }
    return NULL;
}

// Check if exit exists in a direction
bool Room::hasExit(const std::string& direction) const {
    return exits.find(direction) != exits.end();
}

// Clear dead monster from room
void Room::clearMonster() {
    if (monster) {
        delete monster;
        monster = NULL;
    }
}

// Add item to room
void Room::addItem(Item* item) {
    if (item) {
        items.push_back(item);
    }
}

// Remove item from room
void Room::removeItem(const std::string& item_name) {
    for (int i = 0; i < (int)items.size(); i++) {
        if (iequals(items[i]->getName(), item_name)) {
            items.erase(items.begin() + i);  // Don't delete - item moves to player inventory
            return;
        }
    }
}

// Display items in room
void Room::displayItems() const {
    for (int i = 0; i < (int)items.size(); i++) {
        std::cout << "  - " << items[i]->getName() << std::endl;
    }
}

// Get item by name
Item* Room::getItem(const std::string& item_name) {
    for (int i = 0; i < (int)items.size(); i++) {
        if (iequals(items[i]->getName(), item_name)) return items[i];
    }
    return NULL;
}
