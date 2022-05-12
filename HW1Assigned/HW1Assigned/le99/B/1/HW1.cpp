#include <iostream>
#include <sstream>
#include <string>
#include "Automobile.h"

int main(int argc, char* argv[]) 
{
    Automobile* car1 = new Automobile(100000,52000,9,3,2021);
    std::cout << "Vehicle ID: " + std::to_string(car1->getvehID()) << std::endl;
    std::cout << "Milage: " + std::to_string(car1->getMiles()) << std::endl;
    std::cout << "Last Maintainance Date: " + (car1->getmtnDate()) << std::endl;

    Automobile* car2 = new Automobile(100001,27000,8,25,2021);
    std::cout << "Vehicle ID: " + std::to_string(car2->getvehID()) << std::endl;
    std::cout << "Milage: " + std::to_string(car2->getMiles()) << std::endl;
    std::cout << "Last Maintainance Date: " + (car2->getmtnDate()) << std::endl; 
}