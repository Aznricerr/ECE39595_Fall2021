#include "Creature.h"

#ifdef STEP1_DEBUG
#include <iostream>
#endif

Creature::Creature() : DungeonElement("")
{
    this->attack = nullptr;

#ifdef STEP1_DEBUG
    std::cout << "Creature Constructor" << std::endl;
#endif
}

Creature::Creature(std::string name) : DungeonElement(name)
{
    this->attack = nullptr;

#ifdef STEP1_DEBUG
    std::cout << "Creature Constructor with name " + name + " " << std::endl;
#endif
}

ConditionalExecutable *Creature::get_attack()
{
    return (this->attack);
}

void Creature::set_attack(ConditionalExecutable *attack)
{
    this->attack = attack;
}

void Creature::add_vulnerability(std::string vulnerability)
{
    vulnerabilities[vulnerability] = true;
}

bool Creature::is_vulnerability(std::string vulnerability)
{
    if (this->vulnerabilities.find(vulnerability) == this->vulnerabilities.end())
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

bool Creature::is_conditions_met(Item *item)
{
    if ((this->get_attack() == nullptr) || (this->get_attack()->get_conditions().size() == 0))
    {
        return (true);
    }

    for (unsigned int i = 0; i < this->get_attack()->get_conditions().size(); i++)
    {
        if (this->get_attack()->get_conditions()[i]->get_type() == "status")
        {
            if (item->get_status() != this->get_attack()->get_conditions()[i]->get_status())
            {
                return (false);
            }
        }
        else if (this->get_attack()->get_conditions()[i]->get_type() == "owner")
        {
            continue;
            //TODO: IMPLEMENT OWNERSHIP CHECK
        }
    }

    return (true);
}