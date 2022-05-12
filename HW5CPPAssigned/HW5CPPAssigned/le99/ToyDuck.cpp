#include <iostream>
#include "ToyDuck.h"
#include "FlyNoWay.h"
#include "Quack.h"
#include "LaysToyEggs.h"

ToyDuck::ToyDuck()
{
    quackBehavior = new Quack();
    flyBehavior = new FlyNoWay();
    layeggs = new LaysToyEggs();
}

void ToyDuck::display()
{
    std::cout << "I’m a toy duck." << std::endl;
}