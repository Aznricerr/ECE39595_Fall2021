#ifndef _ROOM_H_
#define _ROOM_H_

#include <string>
#include <vector>
#include <unordered_map>

#include "DungeonElementHolder.h"
#include "Item.h"
#include "Container.h"
#include "Creature.h"
#include "Trigger.h"
#include "Border.h"
#include "Map.h"

class Room : public DungeonElementHolder
{
public:
    Room();
    std::string get_type();
    void set_type(std::string type);
    Container *get_container(std::string name);
    void add_container(Container *container);
    std::string get_border_name(direction_t direction);
    void set_border_name(direction_t direction, std::string name);
    void remove_item(std::string name);
    Container *get_container_with_item(std::string name);
    std::unordered_map<std::string, Container *> get_containers();

private:
    std::string type;
    std::unordered_map<std::string, Container *> containers;
    std::vector<Border *> borders;
};

#endif