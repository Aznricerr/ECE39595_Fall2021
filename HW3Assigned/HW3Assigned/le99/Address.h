#ifndef ADDRESS_H_
#define ADDRESS_H_
#include <string>

class Address
{
public:
   Address(const std::string &_street, const std::string &_city, const std::string &_state, int _zip);
   virtual int getZipCode();
   virtual std::string getAddress();

private:
   std::string street;
   std::string city;
   std::string state;
   int zip;
};
#endif /* ADDRESS_H_ */
