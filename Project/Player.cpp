#include <iostream>

#include "Player.h"

Player::Player()
{
}

Player::Player(Map *map)
{
    this->map = map;

    this->current_room = static_cast<Room *>(this->map->get_dungeon_element("Entrance"));
    std::cout << current_room->get_description() << std::endl;
}

Room *Player::get_current_room()
{
    return (this->current_room);
}

void Player::set_current_room(Room *current_room)
{
    this->current_room = current_room;
}

void Player::move_to_next_room(direction_t direction)
{
    if (this->get_current_room()->get_border_name(direction) == "")
    {
        std::cout << "Can't go that way." << std::endl;
    }
    else
    {
        std::string next_room_name = current_room->get_border_name(direction);
        Room *next_room = static_cast<Room *>(map->get_dungeon_element(next_room_name));
        this->set_current_room(next_room);
        std::cout << this->get_current_room()->get_description() << std::endl;
    }
}

Item *Player::get_item_from_inventory(std::string name)
{
    if ((this->inventory).find(name) == (this->inventory).end())
    {
        return (nullptr);
    }
    else
    {
        return (this->inventory[name]);
    }
}

void Player::add_item_to_inventory(Item *item)
{
    this->inventory[item->get_name()] = item;
    std::cout << "Item " + item->get_name() + " added to the inventory." << std::endl;
}

void Player::remove_item_from_inventory(std::string name)
{
    this->inventory.erase(name);
}

void Player::print_inventory()
{
    std::cout << "Inventory: ";

    if (inventory.empty())
    {
        std::cout << "empty" << std::endl;
    }
    else
    {
        for (auto current_item = this->inventory.begin(); current_item != this->inventory.end(); current_item++)
        {
            if (current_item == this->inventory.begin())
            {
                std::cout << current_item->first;
            }
            else if (current_item == this->inventory.end())
            {
                std::cout << ", " + current_item->first;
            }
            else
            {
                std::cout << ", " + current_item->first;
            }
        }

        std::cout << std::endl;
    }
}