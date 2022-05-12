#ifndef _XMLPARSER_H_
#define _XMLPARSER_H_

#include <string>

#include "tinyxml.h"
#include "Map.h"
#include "Room.h"
#include "Item.h"
#include "Trigger.h"
#include "Border.h"
#include "ConditionalExecutable.h"

class XMLParser
{
private:
    Map *parse_map(TiXmlElement *element);
    Room *parse_room(TiXmlElement *element, Map *map);
    Item *parse_item_from_dungeon_element(TiXmlElement *element, Map *map);
    Item *parse_item_from_map(TiXmlElement *element, Map *map);
    Container *parse_container_from_room(TiXmlElement *element, Map *map);
    Container *parse_container_from_map(TiXmlElement *element, Map *map);
    Creature *parse_creature_from_room(TiXmlElement *element, Map *map);
    Creature *parse_creature_from_map(TiXmlElement *element, Map *map);
    Trigger *parse_trigger(TiXmlElement *element);
    ConditionalExecutable *parse_conditional_executable(TiXmlElement *element);

public:
    Map *parse_XML(std::string filename);
};
#endif