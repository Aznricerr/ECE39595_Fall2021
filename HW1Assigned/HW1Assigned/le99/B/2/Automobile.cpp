#include <iostream>
#include <sstream>
#include <string>
#include "Automobile.h"

Automobile::Automobile(int inpID, float inpMIL, int inpMonth, int inpDay, int inpYear)
{
    vehID = inpID;
    miles = inpMIL;
    month = inpMonth;
    day = inpDay;
    year = inpYear;
}

int Automobile::getvehID()
{
    return vehID;
}

float Automobile::getMiles()
{
    return miles;
}


int Automobile::getMonth()
{
    return month;
}

int Automobile::getDay()
{
    return day;
}

int Automobile::getYear()
{
    return year;
}

std::string Automobile::retString()
{
    return ""+std::to_string(month)+"/"+std::to_string(day)+"/"+std::to_string(year);
}
