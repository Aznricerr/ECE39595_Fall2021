#include <iostream>
#include "MallardDuck.h"
#include "Quack.h"
#include "FlyWithWings.h"
#include "LaysEggsBroody.h"

MallardDuck::MallardDuck()
{
   quackBehavior = new Quack();
   flyBehavior = new FlyWithWings();
   layeggs = new LaysEggsBroody();
}

void MallardDuck::display()
{
   std::cout << "I’m a real mallard duck" << std::endl;
}
