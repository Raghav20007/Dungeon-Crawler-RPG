## Dungeon Crawler RPG

A text-based, turn-based dungeon crawler written in C++. You explore a small dungeon, fight monsters, collect and equip items, level up, and try to defeat the dragon in the throne room.
The project demonstrates class hierarchies, constructor chaining, virtual functions and polymorphism, STL containers, and manual memory management with new/delete.

## Table of Contents
- Quick Start
- How to Play
- The Dungeon
- Project Structure
- Class Hierarchy
- Game Mechanics
- Part 1: Files I Implemented
- Part 2: Files Provided by the Instructor
- Credits


## Quick Start

You need a C++ compiler (g++ or clang++).

bash
git clone https://github.com/YOUR-USERNAME/YOUR-REPO.git
cd YOUR-REPO
g++ -g *.cpp -o main
./main            # Windows PowerShell: .\main.exe

If *.cpp does not expand on your shell (common in Windows PowerShell), list the files explicitly:

bash
g++ -g main.cpp Character.cpp Game.cpp Item.cpp Monster.cpp Player.cpp Room.cpp -o main

All .cpp files must be compiled together. The .h files are included automatically.

## How to Play

Enter your name, then type commands at the > prompt. Commands are not case-sensitive.

Command	Description
go <direction>	Move north, south, east or west
look	Redisplay the current room
attack	Start combat with the monster in the room
pickup <item>	Pick up an item from the room
inventory	List the items you are carrying
equip <item>	Equip a weapon or armor
use <item>	Use a consumable (potion, food)
stats	Show your level, HP, attack, defense, gold and XP
help	Show the command list
quit	Exit the game

During combat you choose one action per turn: attack, use <item>, or flee.

Goal: defeat the Dragon in the Throne Room. If your HP reaches 0, the game is over.

## The Dungeon
                 [ Throne Room ]
                   (Dragon)
                       |
 [ Armory ] ---- [ Long Hallway ] ---- [ Treasury ]
  (Skeleton)        (Goblin)            (Skeleton)
                       |
              [ Dungeon Entrance ]

You cannot leave a room while a monster is still alive in it, so every room must be cleared before you move on. Monsters drop loot into the room when defeated.

## Project Structure
.
├── main.cpp          Entry point
├── Game.h / .cpp     Game engine: world setup, command loop, combat
├── Room.h / .cpp     Rooms, exits, items and monsters in a room
├── Character.h / .cpp  Base class for the player and monsters
├── Player.h / .cpp   The player: inventory, equipment, leveling
├── Monster.h / .cpp  Monster base class plus Goblin, Skeleton, Dragon
├── Item.h / .cpp     Item base class plus Weapon, Armor, Consumable
└── README.md

## Class Hierarchy

Character                  Item
├── Player                 ├── Weapon
└── Monster                ├── Armor
    ├── Goblin             └── Consumable
    ├── Skeleton
    └── Dragon

Game  ──owns──>  Player, Room(s)
Room  ──owns──>  Monster, Item(s), and links to neighboring Rooms

Virtual functions (calculateDamage, displayStats, displayInfo, getAttackMessage) and virtual destructors let the game treat monsters and items polymorphically through base-class pointers.

## Game Mechanics
Damage: a character's attack roll is attack + random(0–4). The Player adds the equipped weapon's bonus. The Dragon adds a flat +5 fire damage. The target subtracts its defense from the roll, and damage never goes below 0.
Healing: potions and food restore HP, capped at max HP.
Leveling: you need level × 100 XP to level up. A level-up resets XP, adds +10 max HP, +2 attack and +1 defense, and fully heals you.
Loot: each monster type carries its own loot, which is dropped into the room on death. Ownership of the loot items moves from the monster to the room, then to your inventory when you pick them up.
Memory: every Player, Monster, Room and Item that owns heap memory frees it in its destructor.

## Part 1: Files I Implemented

These four files are the ones I wrote. Constructors and a few helpers inside them were supplied.

Character.cpp
Implements the shared behavior for everything that can fight.

calculateDamage() returns attack plus a random bonus of 0–4.
takeDamage() subtracts defense (minimum 0 damage), reduces HP, clamps HP at 0, marks the character dead when HP runs out, and prints Name takes X damage! (Y/Z HP).
heal() restores HP up to the maximum and reports the amount actually healed.
displayStats() prints Name [HP: current/max].
Provided: the constructor and the operator<< overload.
Item.cpp
Implements the item classes and how each one displays itself.

Item::displayInfo() and displayBrief() print the item's name, description, value and type.
Weapon, Armor and Consumable each override displayInfo() with their own header ([WEAPON], [ARMOR], [CONSUMABLE]) and bonus line.
Consumable::use() marks the item as used and prints a message, or reports that it has already been used.
Provided: all constructors and the operator<< overload.
Player.cpp
Implements the player character, which extends Character.

The destructor deletes every item left in the inventory to avoid memory leaks.
displayStats() shows level, HP, attack and defense with equipment bonuses, gold and experience.
calculateDamage() overrides the base version to include the equipped weapon's bonus.
Inventory management: addItem, removeItem (also clears equipped pointers if that item was equipped), displayInventory, hasItem and getItem. All name lookups are case-insensitive.
Equipment: equipWeapon, equipArmor, unequipWeapon and unequipArmor, with type checking and error messages.
useItem() heals the player with a consumable and removes it from the inventory.
gainExperience() and levelUp() handle progression.
Provided: the constructor, the case-insensitive iequals helper, and saveToFile / loadFromFile.
Monster.cpp
Implements the monster base class and the three enemy types.

The destructor deletes any loot the monster still owns.
addLoot() stores a non-null item in the loot table.
dropLoot() returns the loot and empties the monster's list, so ownership transfers cleanly and nothing is double-deleted.
getAttackMessage() and displayStats() provide the default text.
Goblin (30 HP) drops a Small Potion, Skeleton (40 HP) drops a Sharp Iron Sword, and Dragon (80 HP) drops armor, a sword and a Large Potion. Each has its own attack message.
Dragon::calculateDamage() is overridden to add +5 fire damage.
Provided: the base Monster constructor.

## Part 2: Files Provided by the Instructor

The following files were supplied in the course starter code and are included so the project builds and runs. They are the work of the course staff, not mine.
main.cpp

The program entry point. It seeds the random number generator, creates a Game object, calls run(), and catches any exception.
Game.h / Game.cpp

The game engine. It builds the five-room world and connects the rooms, gives the player a starting inventory (Rusty Dagger and Bread), runs the main command loop, and parses commands. It also implements movement, the turn-based combat loop, picking up items, and the win and lose conditions. The save and load commands are stubs that print "not yet implemented".
Room.h / Room.cpp

Defines a location in the dungeon: its name and description, an optional monster, a list of items, and a map of exits to neighboring rooms. It handles displaying the room, adding and removing items, and clearing a defeated monster.
Character.h, Item.h, Player.h, Monster.h

The class declarations that define the interfaces for the classes I implemented in Part 1: the member variables, the virtual functions, and the getters and setters. I implemented the corresponding .cpp files but did not design these interfaces.

## Credits
Instructor: Pedro Santacruz. Thank you to the instructor and course staff for the starter code and the game engine.
Implementation of Character.cpp, Item.cpp, Player.cpp and Monster.cpp: Raghav
