#include <iostream>
#include <sstream>
#include <string>
#include "Automobile.h"

Automobile::Automobile(int inpID, float inpMIL, int inpMonth, int inpDay, int inpYear)
{
    vehID = inpID;
    miles = inpMIL;
    mtnDate = ""+std::to_string(inpMonth)+"/"+std::to_string(inpDay)+"/"+std::to_string(inpYear);
}

int Automobile::getvehID()
{
    return vehID;
}

float Automobile::getMiles()
{
    return miles;
}

std::string Automobile::getmtnDate()
{
    return mtnDate;
}
