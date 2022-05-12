#include <string>
#include <iostream>

#include "tinyxml.h"
#include "XMLParser.h"
#include "Map.h"
#include "Room.h"
#include "Item.h"
#include "Container.h"
#include "Creature.h"
#include "Trigger.h"

Map *XMLParser::parse_XML(std::string filename)
{
    TiXmlDocument doc(filename);
    doc.LoadFile();

    TiXmlElement *rootElement = doc.RootElement();
    if (rootElement == NULL)
    {
        std::cerr << "Invalid XML file, contains no data" << std::endl;
        return (NULL);
    }
    if (rootElement->ValueStr() != "map")
    {
        std::cerr << "Invalid XML file, should start with a Pap object" << std::endl;
        return (NULL);
    }

    return (this->parse_map(rootElement));
}

std::string get_text_from_named_child(TiXmlElement *element, std::string name)
{
    TiXmlElement *child = element->FirstChildElement(name);
    if (child != NULL)
    {
        TiXmlNode *grandchild = child->FirstChild();
        if (grandchild != NULL)
        {
            TiXmlText *text = grandchild->ToText();
            if (text != NULL)
            {
                return text->ValueStr();
            }
        }
    }

    return ("");
}

Map *XMLParser::parse_map(TiXmlElement *element)
{
    Map *map = new Map();

    for (TiXmlNode *node = element->FirstChild(); node != NULL; node = node->NextSibling())
    {
        TiXmlElement *child_element = node->ToElement();
        if (child_element != NULL)
        {
            if (child_element->ValueStr() == "room")
            {
                Room *room = this->parse_room(child_element, map);
                if (room != NULL)
                {
                    map->add_dungeon_element(room);

#ifdef STEP1_DEBUG
                    std::cout << "Added Room " + room->get_name() + " to Map" << std::endl;
#endif
                }
            }
            else if (child_element->ValueStr() == "item")
            {
                Item *item = this->parse_item_from_map(child_element, map);
                if (item != NULL)
                {
                    map->add_dungeon_element(item);

#ifdef STEP1_DEBUG
                    std::cout << "Added Item " + item->get_name() + " to Map" << std::endl;
#endif
                }
            }
            else if (child_element->ValueStr() == "container")
            {
                Container *container = this->parse_container_from_map(child_element, map);
                if (container != NULL)
                {
                    map->add_dungeon_element(container);

#ifdef STEP1_DEBUG
                    std::cout << "Added Container " + container->get_name() + " to Map" << std::endl;
#endif
                }
            }
            else if (child_element->ValueStr() == "creature")
            {
                Creature *creature = this->parse_creature_from_map(child_element, map);
                if (creature != NULL)
                {
                    map->add_dungeon_element(creature);

#ifdef STEP1_DEBUG
                    std::cout << "Added Creature " + creature->get_name() + " to Map" << std::endl;
#endif
                }
            }
        }
    }

    return (map);
}

Room *XMLParser::parse_room(TiXmlElement *element, Map *map)
{
    Room *room = new Room();
    room->set_element_type(ROOM);

    for (TiXmlNode *node = element->FirstChild(); node != NULL; node = node->NextSibling())
    {
        TiXmlElement *child_element = node->ToElement();
        if (child_element != NULL)
        {
            if (child_element->ValueStr() == "name")
            {
                std::string name = child_element->GetText();
                room->set_name(name);

#ifdef STEP1_DEBUG
                    std::cout << "Set Room name to " + room->get_name() << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "description")
            {
                std::string description = child_element->GetText();
                room->set_description(description);

#ifdef STEP1_DEBUG
                    std::cout << "Set Room description to " + room->get_description() << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "type")
            {
                std::string type = child_element->GetText();
                room->set_type(type);

#ifdef STEP1_DEBUG
                    std::cout << "Set Room type to " + room->get_type() << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "status")
            {
                std::string status = child_element->GetText();
                room->set_status(status);

#ifdef STEP1_DEBUG
                    std::cout << "Set Room status to " + room->get_status() << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "border")
            {
                std::string direction_string = get_text_from_named_child(child_element, "direction");
                direction_t direction;
                if (direction_string == "north")
                {
                    direction = NORTH;
                }
                else if (direction_string == "south")
                {
                    direction = SOUTH;
                }
                else if (direction_string == "east")
                {
                    direction = EAST;
                }
                else if (direction_string == "west")
                {
                    direction = WEST;
                }
                std::string name = get_text_from_named_child(child_element, "name");
                room->set_border_name(direction, name);

#ifdef STEP1_DEBUG
                    std::cout << "Set Room " + direction_string + " border to " + room->get_border_name(direction) << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "item")
            {
                Item *item = this->parse_item_from_dungeon_element(child_element, map);
                room->add_item(item);

#ifdef STEP1_DEBUG
                    std::cout << "Added item " + item->get_name() + " to Room" << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "container")
            {
                Container *container = this->parse_container_from_room(child_element, map);
                room->add_container(container);

#ifdef STEP1_DEBUG
                    std::cout << "Added Container " + container->get_name() + " to Room" << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "creature")
            {
                Creature *creature = this->parse_creature_from_room(child_element, map);
                room->add_creature(creature);

#ifdef STEP1_DEBUG
                    std::cout << "Added creature " + creature->get_name() + " to Room" << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "trigger")
            {
                Trigger *trigger = this->parse_trigger(child_element);
                room->add_trigger(trigger);

#ifdef STEP1_DEBUG
                    std::cout << "Added trigger to Room" << std::endl;
#endif
            }
        }
    }

    return (room);
}

Item *XMLParser::parse_item_from_dungeon_element(TiXmlElement *element, Map *map)
{
    Item *item;

    std::string name = element->GetText();

    if (map->is_dungeon_element_defined(name))
    {
        item = static_cast<Item *>(map->get_dungeon_element(name));

#ifdef STEP1_DEBUG
                    std::cout << "Retrieved Item " + item->get_name() + " from Map" << std::endl;
#endif

        return (item);
    }
    else
    {
        item = new Item(name);
        item->set_element_type(ITEM);
        map->add_dungeon_element(item);

#ifdef STEP1_DEBUG
                    std::cout << "Added Item " + item->get_name() + " to Map" << std::endl;
#endif

        return (item);
    }
}

Item *XMLParser::parse_item_from_map(TiXmlElement *element, Map *map)
{
    Item *item;

    std::string name = get_text_from_named_child(element, "name");

    if (map->is_dungeon_element_defined(name))
    {
        item = static_cast<Item *>(map->get_dungeon_element(name));

#ifdef STEP1_DEBUG
                    std::cout << "Retrieved Item " + item->get_name() + " from Map" << std::endl;
#endif
    }
    else
    {
        item = new Item(name);
        item->set_element_type(ITEM);
    }

    for (TiXmlNode *node = element->FirstChild(); node != NULL; node = node->NextSibling())
    {
        TiXmlElement *child_element = node->ToElement();
        if (child_element != NULL)
        {
            if (child_element->ValueStr() == "status")
            {
                std::string status = child_element->GetText();
                item->set_status(status);
#ifdef STEP1_DEBUG
                    std::cout << "Set Item status to " + item->get_status() << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "description")
            {
                std::string description = child_element->GetText();
                item->set_description(description);

#ifdef STEP1_DEBUG
                    std::cout << "Set Item description to " + item->get_description() << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "writing")
            {
                std::string writing = child_element->GetText();
                item->set_writing(writing);

#ifdef STEP1_DEBUG
                    std::cout << "Set Item writing to " + item->get_writing() << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "turnon")
            {
                ConditionalExecutable *turnon = this->parse_conditional_executable(child_element);
                item->set_turnon(turnon);

#ifdef STEP1_DEBUG
                    std::cout << "Set Item turnon" << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "trigger")
            {
                Trigger *trigger = this->parse_trigger(child_element);
                item->add_trigger(trigger);

#ifdef STEP1_DEBUG
                    std::cout << "Added trigger to Item" << std::endl;
#endif
            }
        }
    }

    return (item);
}

Container *XMLParser::parse_container_from_room(TiXmlElement *element, Map *map)
{
    Container *container;

    std::string name = element->GetText();

    if (map->is_dungeon_element_defined(name))
    {
        container = static_cast<Container *>(map->get_dungeon_element(name));

#ifdef STEP1_DEBUG
                    std::cout << "Retrieved Container " + container->get_name() + " from Map" << std::endl;
#endif

        return (container);
    }
    else
    {
        container = new Container(name);
        container->set_element_type(CONTAINER);
        map->add_dungeon_element(container);

#ifdef STEP1_DEBUG
                    std::cout << "Added Container " + container->get_name() + " to Map" << std::endl;
#endif

        return (container);
    }
}

Container *XMLParser::parse_container_from_map(TiXmlElement *element, Map *map)
{
    Container *container;

    std::string name = get_text_from_named_child(element, "name");

    if (map->is_dungeon_element_defined(name))
    {
        container = static_cast<Container *>(map->get_dungeon_element(name));

#ifdef STEP1_DEBUG
                    std::cout << "Retrieved Container " + container->get_name() + " from Map" << std::endl;
#endif
    }
    else
    {
        container = new Container(name);
        container->set_element_type(CONTAINER);
    }

    for (TiXmlNode *node = element->FirstChild(); node != NULL; node = node->NextSibling())
    {
        TiXmlElement *child_element = node->ToElement();
        if (child_element != NULL)
        {
            if (child_element->ValueStr() == "status")
            {
                std::string status = child_element->GetText();
                container->set_status(status);

#ifdef STEP1_DEBUG
                    std::cout << "Set Container status to " + container->get_status() << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "description")
            {
                std::string description = child_element->GetText();
                container->set_description(description);

#ifdef STEP1_DEBUG
                    std::cout << "Set Container description to " + container->get_description() << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "accept")
            {
                std::string accept = child_element->GetText();
                container->add_accept(accept);

#ifdef STEP1_DEBUG
                    std::cout << "Added accept " + accept + " to Container" << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "item")
            {
                Item *item = this->parse_item_from_dungeon_element(child_element, map);
                container->add_item(item);

#ifdef STEP1_DEBUG
                    std::cout << "Added item " + item->get_name() + " to Container" << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "trigger")
            {
                Trigger *trigger = this->parse_trigger(child_element);
                container->add_trigger(trigger);

#ifdef STEP1_DEBUG
                    std::cout << "Added trigger to Container" << std::endl;
#endif
            }
        }
    }

    return (container);
}

Creature *XMLParser::parse_creature_from_room(TiXmlElement *element, Map *map)
{
    Creature *creature;

    std::string name = element->GetText();

    if (map->is_dungeon_element_defined(name))
    {
        creature = static_cast<Creature *>(map->get_dungeon_element(name));

#ifdef STEP1_DEBUG
                    std::cout << "Retrieved Creature " + creature->get_name() + " from Map" << std::endl;
#endif

        return (creature);
    }
    else
    {
        creature = new Creature(name);
        creature->set_element_type(CREATURE);
        map->add_dungeon_element(creature);

#ifdef STEP1_DEBUG
                    std::cout << "Added Creature " + creature->get_name() + " to Map" << std::endl;
#endif

        return (creature);
    }
}

Creature *XMLParser::parse_creature_from_map(TiXmlElement *element, Map *map)
{
    Creature *creature;

    std::string name = get_text_from_named_child(element, "name");

    if (map->is_dungeon_element_defined(name))
    {
        creature = static_cast<Creature *>(map->get_dungeon_element(name));

#ifdef STEP1_DEBUG
                    std::cout << "Retrieved Creature " + creature->get_name() + " from Map" << std::endl;
#endif
    }
    else
    {
        creature = new Creature(name);
        creature->set_element_type(CREATURE);
    }

    for (TiXmlNode *node = element->FirstChild(); node != NULL; node = node->NextSibling())
    {
        TiXmlElement *child_element = node->ToElement();
        if (child_element != NULL)
        {
            if (child_element->ValueStr() == "status")
            {
                std::string status = child_element->GetText();
                creature->set_status(status);

#ifdef STEP1_DEBUG
                    std::cout << "Set Creature status to " + creature->get_status() << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "description")
            {
                std::string description = child_element->GetText();
                creature->set_description(description);

#ifdef STEP1_DEBUG
                    std::cout << "Set Creature description to " + creature->get_description() << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "vulnerability")
            {
                std::string vulnerability = child_element->GetText();
                creature->add_vulnerability(vulnerability);

#ifdef STEP1_DEBUG
                    std::cout << "Added vulnerability " + vulnerability + " to Creature" << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "attack")
            {
                ConditionalExecutable *attack = this->parse_conditional_executable(child_element);
                creature->set_attack(attack);

#ifdef STEP1_DEBUG
                    std::cout << "Set Creature attack" << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "trigger")
            {
                Trigger *trigger = this->parse_trigger(child_element);
                creature->add_trigger(trigger);

#ifdef STEP1_DEBUG
                    std::cout << "Added trigger to Creature" << std::endl;
#endif
            }
        }
    }

    return (creature);
}

Trigger *XMLParser::parse_trigger(TiXmlElement *element)
{
    Trigger *trigger = new Trigger();

    std::string type = get_text_from_named_child(element, "type");
    if (type != "")
    {
        trigger->set_type(type);

#ifdef STEP1_DEBUG
                    std::cout << "Set Trigger type to " + trigger->get_type() << std::endl;
#endif
    }

    for (TiXmlNode *node = element->FirstChild(); node != NULL; node = node->NextSibling())
    {
        TiXmlElement *child_element = node->ToElement();
        if (child_element != NULL)
        {
            if (child_element->ValueStr() == "condition")
            {
                std::string object = get_text_from_named_child(child_element, "object");
                std::string has = get_text_from_named_child(child_element, "has");
                if (has == "")
                {
                    std::string status = get_text_from_named_child(child_element, "status");
                    trigger->add_condition(object, status);

#ifdef STEP1_DEBUG
                    std::cout << "Added condition for object " + object + " with status " + status + " to Trigger" << std::endl;
#endif
                }
                else
                {
                    std::string owner = get_text_from_named_child(child_element, "owner");
                    trigger->add_condition(object, has, owner);

#ifdef STEP1_DEBUG
                    std::cout << "Added condition for object " + object + " with has " + has + " and owner " + owner + " to Trigger" << std::endl;
#endif
                }
            }
            else if (child_element->ValueStr() == "command")
            {
                std::string command = child_element->GetText();
                trigger->set_command(command);

#ifdef STEP1_DEBUG
                    std::cout << "Added command " + command + " to Trigger" << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "print")
            {
                std::string print = child_element->GetText();
                trigger->add_print(print);

#ifdef STEP1_DEBUG
                    std::cout << "Added print " + print + " to Trigger" << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "action")
            {
                std::string action = child_element->GetText();
                trigger->add_action(action);

#ifdef STEP1_DEBUG
                    std::cout << "Added action " + action + " to Trigger" << std::endl;
#endif
            }
        }
    }

    return (trigger);
}

ConditionalExecutable *XMLParser::parse_conditional_executable(TiXmlElement *element)
{
    ConditionalExecutable *conditional_executable = new ConditionalExecutable();

    for (TiXmlNode *node = element->FirstChild(); node != NULL; node = node->NextSibling())
    {
        TiXmlElement *child_element = node->ToElement();
        if (child_element != NULL)
        {
            if (child_element->ValueStr() == "condition")
            {
                std::string object = get_text_from_named_child(child_element, "object");
                std::string has = get_text_from_named_child(child_element, "has");
                if (has == "")
                {
                    std::string status = get_text_from_named_child(child_element, "status");
                    conditional_executable->add_condition(object, status);

#ifdef STEP1_DEBUG
                    std::cout << "Added condition for object " + object + " with status " + status + " to ConditionalExecutable" << std::endl;
#endif
                }
                else
                {
                    std::string owner = get_text_from_named_child(child_element, "owner");
                    conditional_executable->add_condition(object, has, owner);

#ifdef STEP1_DEBUG
                    std::cout << "Added condition for object " + object + " with has " + has + " and owner " + owner + " to ConditionalExecutable" << std::endl;
#endif
                }
            }
            else if (child_element->ValueStr() == "print")
            {
                std::string print = child_element->GetText();
                conditional_executable->add_print(print);

#ifdef STEP1_DEBUG
                    std::cout << "Added print " + print + " to ConditionalExecutable" << std::endl;
#endif
            }
            else if (child_element->ValueStr() == "action")
            {
                std::string action = child_element->GetText();
                conditional_executable->add_action(action);

#ifdef STEP1_DEBUG
                    std::cout << "Added action " + action + " to ConditionalExecutable" << std::endl;
#endif
            }
        }
    }

    return (conditional_executable);
}