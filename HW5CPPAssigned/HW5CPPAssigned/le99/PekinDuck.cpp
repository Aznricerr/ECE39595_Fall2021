#include <iostream>
#include "Quack.h"
#include "PekinDuck.h"
#include "LaysEggsNotBroody.h"
#include "FliesPoorly.h"

PekinDuck::PekinDuck()
{
    quackBehavior = new Quack();
    flyBehavior = new FliesPoorly();
    layeggs = new LaysEggsNotBroody();
}

void PekinDuck::display()
{
    std::cout << "I’m a real pekin duck" << std::endl;
}