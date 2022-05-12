#include "Trigger.h"

#ifdef STEP1_DEBUG
#include <iostream>
#endif

Trigger::Trigger()
{
    this->type = "single";
    this->command = "";
    this->valid = true;

#ifdef STEP1_DEBUG
    std::cout << "Trigger Constructor" << std::endl;
#endif
}

std::string Trigger::get_type()
{
    return (this->type);
}

void Trigger::set_type(std::string type)
{
    this->type = type;
}

std::string Trigger::get_command()
{
    return (this->command);
}

void Trigger::set_command(std::string command)
{
    this->command = command;
}

bool Trigger::is_valid()
{
    return (this->valid);
}

void Trigger::set_valid()
{
    this->valid = true;
}

void Trigger::set_invalid()
{
    this->valid = false;
}