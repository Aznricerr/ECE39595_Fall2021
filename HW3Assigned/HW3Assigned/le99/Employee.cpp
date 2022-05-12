#include "Address.h"
#include "Person.h"
#include "Employee.h"

Employee::Employee(const std::string &name, int birthMonth, int birthDay, int birthYear, Address address, double _salary) : Person(name, birthMonth, birthDay, birthYear, address)
{
   salary = _salary;
}

std::string Employee::getRole()
{
   return "Employee";
}

double Employee::getSalary()
{
   return salary;
}
