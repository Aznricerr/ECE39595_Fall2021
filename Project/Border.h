#ifndef _BORDER_H_
#define _BORDER_H_

#include <string>

enum direction_t
{
    NORTH = 0,
    SOUTH,
    EAST,
    WEST
};

class Border
{
public:
    Border(std::string name, direction_t direction);
    std::string get_name();
    void set_name(std::string name);
    direction_t get_direction();
    void set_direction(direction_t direction);

private:
    std::string name;
    direction_t direction;
};

#endif