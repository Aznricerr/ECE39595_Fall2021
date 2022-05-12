#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <string>
#include <unordered_map>

#include "DungeonElementHolder.h"
#include "Item.h"

class Container : public DungeonElementHolder
{
public:
    Container();
    Container(std::string name);
    bool is_empty();
    void add_accept(std::string name);
    bool is_item_accepted(std::string name);
    void remove_item(std::string name);
    bool has_item(std::string name);
    bool has_accept();
    bool all_items_accepted();

    bool is_open;

private:
    std::unordered_map<std::string, bool> accept;
};

#endif