#include "Border.h"

Border::Border(std::string name, direction_t direction)
{
    this->name = name;
    this->direction = direction;
}

std::string Border::get_name()
{
    return (this->name);
}

void Border::set_name(std::string name)
{
    this->name = name;
}

direction_t Border::get_direction()
{
    return (this->direction);
}

void Border::set_direction(direction_t direction)
{
    this->direction = direction;
}