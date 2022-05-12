#include "Map.h"

#ifdef STEP1_DEBUG
#include <iostream>
#endif

Map::Map()
{
#ifdef STEP1_DEBUG
    std::cout << "Map Constructor" << std::endl;
#endif
}

DungeonElement *Map::get_dungeon_element(std::string name)
{    
    if ((this->dungeon_element_dict).find(name) == (this->dungeon_element_dict).end())
    {
        return (nullptr);
    }
    else
    {
        return (this->dungeon_element_dict[name]);
    }
}

void Map::add_dungeon_element(DungeonElement *dungeon_element)
{
    //this->dungeon_element_dict.insert({name, dungeon_element});
    this->dungeon_element_dict[dungeon_element->get_name()] = dungeon_element;
}

void Map::remove_dungeon_element(std::string name)
{
    this->dungeon_element_dict.erase(name);
}

bool Map::is_dungeon_element_defined(std::string name)
{
    if (this->dungeon_element_dict.find(name) == this->dungeon_element_dict.end())
    {
        return (false);
    }
    else
    {
        return (true);
    }
}