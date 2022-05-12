#ifndef PERSON_H_
#define PERSON_H_
#include "Address.h"

class Person
{
public:
   Person(const std::string &_name, int _birthMonth, int _birthDay, int _birthYear, const Address &_address);
   virtual std::string getRole();
   virtual std::string getName();
   virtual int getZipCode();
   virtual std::string getDateOfBirth();

private:
   std::string name;
   std::string dateOfBirth;
   Address address;
};
#endif /* PERSON_H_ */
