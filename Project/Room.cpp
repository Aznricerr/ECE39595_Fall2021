#include "Room.h"

#include <iostream>

#ifdef STEP1_DEBUG
#include <iostream>
#endif

Room::Room()
{
    Border *border_north = new Border("", NORTH);
    Border *border_south = new Border("", SOUTH);
    Border *border_east = new Border("", EAST);
    Border *border_west = new Border("", WEST);
    borders.push_back(border_north);
    borders.push_back(border_south);
    borders.push_back(border_east);
    borders.push_back(border_west);

    this->type = "regular";

#ifdef STEP1_DEBUG
    std::cout << "Room Constructor" << std::endl;
#endif
}

std::string Room::get_type()
{
    return (this->type);
}

void Room::set_type(std::string type)
{
    this->type = type;
}

Container *Room::get_container(std::string name)
{
    if ((this->containers).find(name) == (this->containers).end())
    {
        return (nullptr);
    }
    else
    {
        return (this->containers[name]);
    }
}

void Room::add_container(Container *container)
{
    this->containers[container->get_name()] = container;
}

std::string Room::get_border_name(direction_t direction)
{
    return (this->borders[direction]->get_name());
}

void Room::set_border_name(direction_t direction, std::string name)
{
    this->borders[direction]->set_name(name);
}

void Room::remove_item(std::string name)
{
    if (this->items[name] != nullptr)
    {
        this->items.erase(name);
    }
    else
    {
        for (auto current_container = this->containers.begin(); current_container != containers.end(); current_container++)
        {
            Container *container = current_container->second;

            if (container->get_item(name) != nullptr)
            {
                container->remove_item(name);
            }
        }
    }
}

Container *Room::get_container_with_item(std::string name)
{
    for (auto i = (this->containers).begin(); i != (this->containers).end(); i++)
    {
        Container *container = i->second; 
        if (container->get_item(name) != nullptr)
        {
            return (container);
        }
    }

    return (nullptr);
}

std::unordered_map<std::string, Container *> Room::get_containers()
{
    return (this->containers);
}