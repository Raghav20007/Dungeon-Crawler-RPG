#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Room.h"
#include "Monster.h"
#include "Item.h"
#include <string>
#include <map>

class Game {
private:
    Player* player;
    std::map<std::string, Room*> world;
    Room* current_room;
    bool game_over;
    bool victory;

    // Private helper methods
    void initializeWorld();
    void createStartingInventory();
    void addRoom(Room* room);
    void connectRooms(const std::string& room1_name, const std::string& direction,
                     const std::string& room2_name);

    // Command handlers
    void processCommand(const std::string& command);
    void move(const std::string& direction);
    void look();
    void attack();
    void combat(Monster* monster);
    void pickupItem(const std::string& item_name);
    void inventory();
    void useItem(const std::string& item_name);
    void equipItem(const std::string& item_name);
    void help();
    void save(const std::string& filename);
    void load(const std::string& filename);

public:
    Game();
    ~Game();

    void run();
};

#endif
