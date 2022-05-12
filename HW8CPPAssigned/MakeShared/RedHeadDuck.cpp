#include <iostream>
#include "RedHeadDuck.h"
#include "Quack.h"
#include "FlyWithWings.h"
#include <memory>

RedHeadDuck::RedHeadDuck()
{
   quackBehavior = std::make_shared<Quack>(Quack());
   flyBehavior = std::make_shared<FlyWithWings>(FlyWithWings());
}
void RedHeadDuck::display()
{
   std::cout << "I’m a real redheaded duck" << std::endl;
}
