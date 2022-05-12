#include "DungeonElement.h"

#include <iostream>

#ifdef STEP1_DEBUG
#include <iostream>
#endif

DungeonElement::DungeonElement()
{
    this->name = "";
    this->element_type = DEFAULT;
    this->set_object_existance(true);

#ifdef STEP1_DEBUG
    std::cout << "DungeonElement Constructor" << std::endl;
#endif
}

DungeonElement::DungeonElement(std::string name)
{
    this->name = name;
    this->element_type = DEFAULT;
    this->set_object_existance(true);

#ifdef STEP1_DEBUG
    std::cout << "DungeonElement Constructor with name " + name + " " << std::endl;
#endif
}

std::string DungeonElement::get_name()
{
    return (this->name);
}

void DungeonElement::set_name(std::string name)
{
    this->name = name;
}

std::string DungeonElement::get_status()
{
    return (this->status);
}

void DungeonElement::set_status(std::string status)
{
    this->status = status;
}

std::string DungeonElement::get_description()
{
    return (this->description);
}

void DungeonElement::set_description(std::string description)
{
    this->description = description;
}

element_type_t DungeonElement::get_element_type()
{
    return (this->element_type);
}

bool DungeonElement::does_object_exist_in_map()
{
    return (this->exists_in_map);
}

void DungeonElement::set_object_existance(bool existance)
{
    this->exists_in_map = existance;
}

void DungeonElement::set_element_type(element_type_t element_type)
{
    this->element_type = element_type;
}

std::vector<Trigger *> DungeonElement::get_triggers()
{
    return (this->triggers);
}

void DungeonElement::add_trigger(Trigger *trigger)
{
    this->triggers.push_back(trigger);
}