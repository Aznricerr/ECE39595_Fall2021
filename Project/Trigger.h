#ifndef _TRIGGER_H_
#define _TRIGGER_H_

#include <string>

#include "ConditionalExecutable.h"

class Trigger : public ConditionalExecutable
{
public:
    Trigger();
    std::string get_type();
    void set_type(std::string type);
    std::string get_command();
    void set_command(std::string command);
    bool is_valid();
    void set_valid();
    void set_invalid();
private:
    bool valid;
    std::string type;
    std::string command;
};

#endif