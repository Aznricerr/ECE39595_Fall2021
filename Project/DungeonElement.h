#ifndef _DUNGEONELEMENT_H_
#define _DUNGEONELEMENT_H_

#include <string>
#include <vector>
#include <unordered_map>

#include "Trigger.h"

enum element_type_t {ROOM, ITEM, CONTAINER, CREATURE, DEFAULT};

class DungeonElement
{
public:
    DungeonElement();
    DungeonElement(std::string name);
    std::string get_name();
    void set_name(std::string name);
    std::string get_status();
    void set_status(std::string status);
    std::string get_description();
    void set_description(std::string description);
    element_type_t get_element_type();
    void set_element_type(element_type_t element_type);
    bool does_object_exist_in_map();
    void set_object_existance(bool existance);
    std::vector<Trigger *> get_triggers();
    void add_trigger(Trigger *trigger);

private:
    std::string name;
    std::string status;
    std::string description;
    element_type_t element_type;
    bool exists_in_map;
    std::vector<Trigger *> triggers;
};

#endif