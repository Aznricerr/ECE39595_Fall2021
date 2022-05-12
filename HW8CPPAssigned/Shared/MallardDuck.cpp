#include <iostream>
#include "MallardDuck.h"
#include "Quack.h"
#include "FlyWithWings.h"

MallardDuck::MallardDuck()
{
   quackBehavior = std::shared_ptr<Quack>(new Quack());
   flyBehavior = std::shared_ptr<FlyWithWings>(new FlyWithWings());
}

void MallardDuck::display()
{
   std::cout << "I’m a real mallard duck" << std::endl;
}
