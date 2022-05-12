#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>
#include <unordered_map>

#include "DungeonElement.h"
#include "ConditionalExecutable.h"

class Item : public DungeonElement
{
public:
    Item();
    Item(std::string name);
    std::string get_writing();
    void set_writing(std::string writing);
    ConditionalExecutable *get_turnon();
    void set_turnon(ConditionalExecutable *turnon);
private:
    std::string writing;
    ConditionalExecutable *turnon;
};

#endif