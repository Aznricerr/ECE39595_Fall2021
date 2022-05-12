#include <string>
#include "Address.h"

Address::Address(const std::string &_street, const std::string &_city, const std::string &_state, int _zip)
{
   street = _street;
   city = _city;
   state = _state;
   zip = _zip;
}

int Address::getZipCode()
{
   return zip;
}

std::string Address::getAddress()
{
   return "" + street + "\n" + city + "\n" + state + "\n" + std::to_string(zip);
}
