#include <iostream>
#include "MallardDuck.h"
#include "Quack.h"
#include "FlyWithWings.h"
#include <memory>

MallardDuck::MallardDuck()
{
   quackBehavior = std::make_shared<Quack>(Quack());
   flyBehavior = std::make_shared<FlyWithWings>(FlyWithWings());
}

void MallardDuck::display()
{
   std::cout << "I’m a real mallard duck" << std::endl;
}
