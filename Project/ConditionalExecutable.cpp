#include "ConditionalExecutable.h"

std::vector<Condition *> ConditionalExecutable::get_conditions()
{
    return (this->conditions);
}

void ConditionalExecutable::add_condition(std::string name, std::string status)
{
    Condition *condition = new Condition(name, status);
    this->conditions.push_back(condition);
}

void ConditionalExecutable::add_condition(std::string name, std::string has, std::string owner)
{
    Condition *condition = new Condition(name, has == "yes" ? true : false, owner);
    this->conditions.push_back(condition);
}

std::vector<std::string> ConditionalExecutable::get_prints()
{
    return (this->prints);
}

void ConditionalExecutable::add_print(std::string print)
{
    this->prints.push_back(print);
}
std::vector<std::string> ConditionalExecutable::get_actions()
{
    return (this->actions);
}

void ConditionalExecutable::add_action(std::string action)
{
    this->actions.push_back(action);
}