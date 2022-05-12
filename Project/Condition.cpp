#include "Condition.h"

#ifdef STEP1_DEBUG
#include <iostream>
#endif

Condition::Condition()
{
    this->type = "";
    this->object = "";
    this->status = "";
    this->has = false;
    this->owner = "";

#ifdef STEP1_DEBUG
    std::cout << "Condition Constructor" << std::endl;
#endif
}

Condition::Condition(std::string object, std::string status)
{
    this->type = "status";
    this->object = object;
    this->status = status;

#ifdef STEP1_DEBUG
    std::cout << "Condition Constructor for object " + object + " with status " + status << std::endl;
#endif
}

Condition::Condition(std::string object, bool has, std::string owner)
{
    this->type = "owner";
    this->object = object;
    this->has = has;
    this->owner = owner;

#ifdef STEP1_DEBUG
    std::cout << "Condition Constructor for object " + object + " with has " + std::to_string(has) + " and owner " + owner << std::endl;
#endif
}

void Condition::set_status_condition(std::string object, std::string status)
{
    this->type = "status";
    this->object = object;
    this->status = status;
}

void Condition::set_owner_condition(std::string object, bool has, std::string owner)
{
    this->type = "owner";
    this->object = object;
    this->has = has;
    this->owner = owner;
}

std::string Condition::get_type()
{
    return (this->type);
}

std::string Condition::get_object()
{
    return (this->object);
}

bool Condition::get_has()
{
    if (this->type == "owner")
    {
        return (this->has);
    }
    else
    {
        return (false);
    }
}
std::string Condition::get_owner()
{
    if (this->type == "owner")
    {
        return (this->owner);
    }
    else
    {
        return ("");
    }
}

std::string Condition::get_status()
{
    if (this->type == "status")
    {
        return (this->status);
    }
    else
    {
        return ("");
    }
}