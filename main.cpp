#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Main entry point for Dungeon Crawler RPG

int main() {
    srand(static_cast<unsigned int>(time(0)));

    try {
        Game game;
        game.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
