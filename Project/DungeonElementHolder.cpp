#ifdef STEP1_DEBUG
#include <iostream>
#endif

#include "DungeonElementHolder.h"

DungeonElementHolder::DungeonElementHolder() : DungeonElement()
{
#ifdef STEP1_DEBUG
    std::cout << "DungeonElementHolder Constructor" << std::endl;
#endif
}

DungeonElementHolder::DungeonElementHolder(std::string name) : DungeonElement(name)
{
#ifdef STEP1_DEBUG
    std::cout << "DungeonElementHolder Constructor with name " + name + " " << std::endl;
#endif
}

Item *DungeonElementHolder::get_item(std::string name)
{
    if ((this->items).find(name) == (this->items).end())
    {
        return (nullptr);
    }
    else
    {
        return (this->items[name]);
    }
}

void DungeonElementHolder::add_item(Item *item)
{
    this->items[item->get_name()] = item;
}

Creature *DungeonElementHolder::get_creature(std::string name)
{
    if ((this->creatures).find(name) == (this->creatures).end())
    {
        return (nullptr);
    }
    else
    {
        return (this->creatures[name]);
    }
}

void DungeonElementHolder::add_creature(Creature *creature)
{
    this->creatures[creature->get_name()] = creature;
}

std::string DungeonElementHolder::print_items()
{
    std::string item_list;
    for (auto i = (this->items).begin(); i != (this->items).end(); i++)
    {
        if (i == (this->items).begin())
        {
            item_list = item_list + i->first;
        }
        else
        {
            item_list = item_list + ", " + i->first;
        }
    }

    return (item_list);
}

std::unordered_map<std::string, Item *> DungeonElementHolder::get_items()
{
    return (this->items);
}

std::unordered_map<std::string, Creature *> DungeonElementHolder::get_creatures()
{
    return (this->creatures);
}