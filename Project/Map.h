#ifndef _MAP_H_
#define _MAP_H_

#include <string>
#include <unordered_map>

#include "DungeonElement.h"
#include "DungeonElementHolder.h"

class Map
{
public:
    Map();
    DungeonElement *get_dungeon_element(std::string name);
    void add_dungeon_element(DungeonElement *dungeon_element);
    void remove_dungeon_element(std::string name);
    bool is_dungeon_element_defined(std::string name);

private:
    std::unordered_map<std::string, DungeonElement *> dungeon_element_dict;
};

#endif