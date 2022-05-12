#ifndef _DUNGEON_ELEMENT_HOLDER_H_
#define _DUNGEON_ELEMENT_HOLDER_H_

#include "DungeonElement.h"
#include "Item.h"
#include "Creature.h"

class DungeonElementHolder : public DungeonElement
{
public:
    DungeonElementHolder();
    DungeonElementHolder(std::string name);
    Item *get_item(std::string name);
    void add_item(Item *item);
    Creature *get_creature(std::string name);
    void add_creature(Creature *creature);
    std::string print_items();
    std::unordered_map<std::string, Item *> get_items();
    std::unordered_map<std::string, Creature *> get_creatures();

protected:
    std::unordered_map<std::string, Item *> items;
    std::unordered_map<std::string, Creature *> creatures;
};

#endif