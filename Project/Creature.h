#ifndef _CREATURE_H_
#define _CREATURE_H_

#include <string>

#include "DungeonElement.h"
#include "ConditionalExecutable.h"
#include "Item.h"

class Creature : public DungeonElement
{
public:
    Creature();
    Creature(std::string name);
    ConditionalExecutable *get_attack();
    void set_attack(ConditionalExecutable *attack);
    void add_vulnerability(std::string vulnerability);
    bool is_vulnerability(std::string vulnerability);
    bool is_conditions_met(Item *item);
private:
    ConditionalExecutable *attack;
    std::unordered_map<std::string, bool> vulnerabilities;
};

#endif