#include "Container.h"

#ifdef STEP1_DEBUG
#include <iostream>
#endif

Container::Container() : DungeonElementHolder("")
{
    this->is_open = false;
#ifdef STEP1_DEBUG
    std::cout << "Container Constructor" << std::endl;
#endif
}

Container::Container(std::string name) : DungeonElementHolder(name)
{
    this->is_open = false;
#ifdef STEP1_DEBUG
    std::cout << "Container Constructor with name " + name + " " << std::endl;
#endif
}

bool Container::is_empty()
{
    if ((this->items).empty())
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

void Container::add_accept(std::string name)
{
    this->accept[name] = true;
}

bool Container::is_item_accepted(std::string name)
{
    if (this->accept.find(name) == this->accept.end())
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

void Container::remove_item(std::string name)
{
    if (this->is_open)
    {
        this->items.erase(name);
    }
}

bool Container::has_item(std::string name)
{
    if (this->get_item(name) == nullptr)
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

bool Container::has_accept()
{
    if ((this->accept).empty())
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

bool Container::all_items_accepted()
{
    for (auto i = (this->accept).begin(); i != (this->accept).end(); i++)
    {
        if (!this->has_item(i->first))
        {
            return (false);
        }
    }

    return (true);
}