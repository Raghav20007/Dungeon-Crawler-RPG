#include "Game.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cctype>

Game::Game() : player(NULL), current_room(NULL),
               game_over(false), victory(false) {
}

Game::~Game() {
    // Clean up player
    if (player) {
        delete player;
    }
    
    // Clean up all rooms
    for (std::map<std::string, Room*>::iterator it = world.begin(); it != world.end(); it++) {
        delete it->second;
    }
    world.clear();
}

// Initialize the game world
void Game::initializeWorld() {
    // Create rooms
    Room* entrance = new Room("Dungeon Entrance", 
        "A dark stone corridor leads deeper into the dungeon. "
        "Torches flicker on the walls.");
    
    Room* hallway = new Room("Long Hallway",
        "A long hallway with cracked stone walls. You hear strange noises ahead.");
    
    Room* armory = new Room("Armory",
        "An old armory with rusty weapons scattered about.");
    
    Room* treasury = new Room("Treasury",
        "A room filled with gold and treasure! But something guards it...");
    
    Room* throne_room = new Room("Throne Room",
        "The final chamber. A massive dragon sits upon a throne of bones.");
    
    // Add rooms to world
    addRoom(entrance);
    addRoom(hallway);
    addRoom(armory);
    addRoom(treasury);
    addRoom(throne_room);
    
    // Connect rooms
    connectRooms("Dungeon Entrance", "north", "Long Hallway");
    connectRooms("Long Hallway", "west", "Armory");
    connectRooms("Long Hallway", "east", "Treasury");
    connectRooms("Long Hallway", "north", "Throne Room");
    
    hallway->setMonster(new Goblin());
    armory->setMonster(new Skeleton());
    treasury->setMonster(new Skeleton());
    throne_room->setMonster(new Dragon());  // Boss fight!
    
    armory->addItem(new Weapon("Iron Sword", "A sturdy iron blade", 8));
    armory->addItem(new Armor("Chain Mail", "Light but protective armor", 5));
    armory->addItem(new Consumable("Health Potion", "Restores 50 HP", 50));
    treasury->addItem(new Consumable("Health Potion", "Restores 50 HP", 50));
    entrance->addItem(new Consumable("Small Potion", "Restores 20 HP", 20));
    
    // Set starting room
    current_room = entrance;
}

// Give player starting items
void Game::createStartingInventory() {
    player->addItem(new Weapon("Rusty Dagger", "A dull, rusty dagger", 2));
    player->addItem(new Consumable("Bread", "A stale piece of bread", 5));
}

// Add room to world
void Game::addRoom(Room* room) {
    if (room) {
        world[room->getName()] = room;
    }
}

// Connect two rooms bidirectionally
void Game::connectRooms(const std::string& room1_name, const std::string& direction,
                       const std::string& room2_name) {
    Room* room1 = world[room1_name];
    Room* room2 = world[room2_name];
    
    if (room1 && room2) {
        room1->addExit(direction, room2);
        
        // Add reverse direction
        std::string reverse;
        if (direction == "north") reverse = "south";
        else if (direction == "south") reverse = "north";
        else if (direction == "east") reverse = "west";
        else if (direction == "west") reverse = "east";
        
        room2->addExit(reverse, room1);
    }
}

// Main game loop
void Game::run() {
    // Create player
    std::string player_name;
    std::cout << "\n=== DUNGEON CRAWLER RPG ===" << std::endl;
    std::cout << "Enter your name, brave adventurer: ";
    std::getline(std::cin, player_name);
    
    player = new Player(player_name);
    
    // Initialize world and inventory
    initializeWorld();
    createStartingInventory();
    
    std::cout << "\nWelcome, " << player_name << "!" << std::endl;
    std::cout << "Your quest: Defeat the dragon in the throne room!" << std::endl;
    std::cout << "Type 'help' for commands.\n" << std::endl;
    
    // Display starting room
    current_room->display();
    current_room->markVisited();
    
    // Main game loop
    while (!game_over) {
        std::cout << "\n> ";
        std::string command;
        std::getline(std::cin, command);
        
        // Convert to lowercase
        for (int i = 0; i < (int)command.length(); i++) {
            command[i] = tolower(command[i]);
        }
        
        if (!command.empty()) {
            processCommand(command);
        }
        
        // Check victory condition
        if (victory) {
            std::cout << "\nVICTORY! You have defeated the dragon!" << std::endl;
            std::cout << "The kingdom is saved!" << std::endl;
            game_over = true;
        }
        
        // Check defeat condition
        if (!player->isAlive()) {
            std::cout << "\nYou have died..." << std::endl;
            std::cout << "Game Over" << std::endl;
            game_over = true;
        }
    }
}

// Process player command
void Game::processCommand(const std::string& command) {
    std::istringstream iss(command);
    std::string verb, object;
    iss >> verb;
    
    // Get rest of command as object
    std::getline(iss, object);
    // Trim leading space
    if (!object.empty() && object[0] == ' ') {
        object = object.substr(1);
    }
    
    if (verb == "go" || verb == "move") {
        if (object.empty()) {
            std::cout << "Go where? (north/south/east/west)" << std::endl;
        } else {
            move(object);
        }
    }
    else if (verb == "look" || verb == "l") {
        look();
    }
    else if (verb == "attack" || verb == "fight") {
        attack();
    }
    else if (verb == "pickup" || verb == "get" || verb == "take") {
        if (object.empty()) {
            std::cout << "Pick up what?" << std::endl;
        } else {
            pickupItem(object);
        }
    }
    else if (verb == "inventory" || verb == "i") {
        inventory();
    }
    else if (verb == "use") {
        if (object.empty()) {
            std::cout << "Use what?" << std::endl;
        } else {
            useItem(object);
        }
    }
    else if (verb == "equip" || verb == "wield" || verb == "wear") {
        if (object.empty()) {
            std::cout << "Equip what?" << std::endl;
        } else {
            equipItem(object);
        }
    }
    else if (verb == "stats") {
        player->displayStats();
    }
    else if (verb == "save") {
        save(object.empty() ? "savegame.txt" : object);
    }
    else if (verb == "load") {
        load(object.empty() ? "savegame.txt" : object);
    }
    else if (verb == "help" || verb == "h" || verb == "?") {
        help();
    }
    else if (verb == "quit" || verb == "exit") {
        std::cout << "Thanks for playing!" << std::endl;
        game_over = true;
    }
    else {
        std::cout << "Unknown command. Type 'help' for commands." << std::endl;
    }
}

// Move to adjacent room
void Game::move(const std::string& direction) {
    if (current_room->hasMonster()) {
        std::cout << "You can't leave while a monster blocks your path!" << std::endl;
        return;
    }
    
    Room* next_room = current_room->getExit(direction);
    if (next_room) {
        current_room = next_room;
        current_room->display();
        current_room->markVisited();
    } else {
        std::cout << "You can't go that way!" << std::endl;
    }
}

// Look around current room
void Game::look() {
    current_room->display();
}

// Attack monster in room
void Game::attack() {
    if (!current_room->hasMonster()) {
        std::cout << "There's nothing to fight here." << std::endl;
        return;
    }
    
    combat(current_room->getMonster());
}

// Combat system - turn-based
void Game::combat(Monster* monster) {
    std::cout << "\n=== COMBAT BEGINS ===" << std::endl;
    
    while (player->isAlive() && monster->isAlive()) {
        // Display status
        std::cout << "\n" << *player << std::endl;
        std::cout << *monster << std::endl;
        
        // Player turn
        std::cout << "\nYour turn! (attack/use <item>/flee): ";
        std::string action;
        std::getline(std::cin, action);
        for (int i = 0; i < (int)action.length(); i++) {
            action[i] = tolower(action[i]);
        }
        
        if (action == "attack") {
            int damage = player->calculateDamage();
            std::cout << "\nYou attack for " << damage << " damage!" << std::endl;
            monster->takeDamage(damage);
            
            if (!monster->isAlive()) {
                // Monster defeated!
                std::cout << "\nVictory! You defeated the " << monster->getName() << "!" << std::endl;
                player->gainExperience(monster->getExperienceReward());
                player->addGold(monster->getGoldReward());
                
                // Drop loot
                std::vector<Item*> loot = monster->dropLoot();
                for (int i = 0; i < (int)loot.size(); i++) {
                    current_room->addItem(loot[i]);
                }
                
                // Check if this was the final boss
                if (monster->getName() == "Dragon") {
                    victory = true;
                }
                
                current_room->clearMonster();
                break;
            }
        }
        else if (action.find("use") == 0) {
            std::string item_name = action.substr(4);
            player->useItem(item_name);
        }
        else if (action == "flee") {
            std::cout << "You flee from combat!" << std::endl;
            break;
        }
        else {
            std::cout << "Invalid action!" << std::endl;
            continue;
        }
        
        // Monster turn
        if (monster->isAlive()) {
            std::cout << "\n" << monster->getAttackMessage() << std::endl;
            int damage = monster->calculateDamage();
            player->takeDamage(damage);
        }
    }
    
    std::cout << "\n=== COMBAT ENDS ===" << std::endl;
}

// Pick up item from room
void Game::pickupItem(const std::string& item_name) {
    Item* item = current_room->getItem(item_name);
    if (item) {
        player->addItem(item);
        current_room->removeItem(item_name);
    } else {
        std::cout << "Item not found: " << item_name << std::endl;
    }
}

// Display inventory
void Game::inventory() {
    player->displayInventory();
}

// Use item from inventory
void Game::useItem(const std::string& item_name) {
    player->useItem(item_name);
}

// Equip item from inventory
void Game::equipItem(const std::string& item_name) {
    Item* item = player->getItem(item_name);
    if (!item) {
        std::cout << "You don't have that item!" << std::endl;
        return;
    }
    
    if (item->getType() == "Weapon") {
        player->equipWeapon(item_name);
    } else if (item->getType() == "Armor") {
        player->equipArmor(item_name);
    } else {
        std::cout << "You can't equip that!" << std::endl;
    }
}

// Save game
void Game::save(const std::string& filename) {
    std::cout << "Save functionality not yet implemented!" << std::endl;
}

// Load game
void Game::load(const std::string& filename) {
    std::cout << "Load functionality not yet implemented!" << std::endl;
}

// Display help
void Game::help() {
    std::cout << "\n=== COMMANDS ===" << std::endl;
    std::cout << "  go <direction>    - Move (north/south/east/west)" << std::endl;
    std::cout << "  look              - Look around current room" << std::endl;
    std::cout << "  attack            - Attack monster in room" << std::endl;
    std::cout << "  pickup <item>     - Pick up item from room" << std::endl;
    std::cout << "  inventory         - Show your inventory" << std::endl;
    std::cout << "  equip <item>      - Equip weapon or armor" << std::endl;
    std::cout << "  use <item>        - Use consumable item" << std::endl;
    std::cout << "  stats             - Show your character stats" << std::endl;
    std::cout << "  save [filename]   - Save game" << std::endl;
    std::cout << "  load [filename]   - Load game" << std::endl;
    std::cout << "  help              - Show this help" << std::endl;
    std::cout << "  quit              - Exit game" << std::endl;
    std::cout << "================\n" << std::endl;
}
