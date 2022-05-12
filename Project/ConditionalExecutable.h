#ifndef _CONDITIONAL_EXECUTABLE_H_
#define _CONDITIONAL_EXECUTABLE_H_

#include <string>
#include <vector>
#include <unordered_map>

#include "Condition.h"

class ConditionalExecutable
{
public:
    std::vector<Condition *> get_conditions();
    void add_condition(std::string name, std::string status);
    void add_condition(std::string name, std::string has, std::string status);
    std::vector<std::string> get_prints();
    void add_print(std::string print);
    std::vector<std::string> get_actions();
    void add_action(std::string action);
private:
    std::vector<Condition *> conditions;
    std::vector<std::string> prints;
    std::vector<std::string> actions;
};

#endif