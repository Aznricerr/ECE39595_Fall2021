#include "Item.h"

#ifdef STEP1_DEBUG
#include <iostream>
#endif

Item::Item() : DungeonElement("")
{
    this->writing = "";
#ifdef STEP1_DEBUG
    std::cout << "Item Constructor" << std::endl;
#endif
}

Item::Item(std::string name) : DungeonElement(name)
{
    this->writing = "";
#ifdef STEP1_DEBUG
    std::cout << "Item Constructor with name " + name + " " << std::endl;
#endif
}

std::string Item::get_writing()
{
    return (this->writing);
}

void Item::set_writing(std::string writing)
{
    this->writing = writing;
}

ConditionalExecutable *Item::get_turnon()
{
    return (this->turnon);
}

void Item::set_turnon(ConditionalExecutable *turnon)
{
    this->turnon = turnon;
}