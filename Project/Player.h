#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <unordered_map>

#include "Map.h"
#include "Room.h"
#include "Item.h"

class Player
{
public:
    Player();
    Player(Map *map);
    Room *get_current_room();
    void set_current_room(Room *);
    void move_to_next_room(direction_t direction);
    Item *get_item_from_inventory(std::string name);
    void add_item_to_inventory(Item *item);
    void remove_item_from_inventory(std::string name);
    void print_inventory();

private:
    Map *map;
    Room *current_room;
    std::unordered_map<std::string, Item *> inventory;
};

#endif