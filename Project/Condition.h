#ifndef _CONDITION_H_
#define _CONDITION_H_

#include <string>

class Condition
{
public:
    Condition();
    Condition(std::string object, std::string status);
    Condition(std::string object, bool has, std::string owner);
    void set_status_condition(std::string object, std::string status);
    void set_owner_condition(std::string object, bool has, std::string owner);
    std::string get_type();
    std::string get_object();
    bool get_has();
    std::string get_owner();
    std::string get_status();
private:
    std::string type;
    std::string object;
    bool has;
    std::string owner;
    std::string status;
};

#endif