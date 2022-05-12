#include <iostream>
#include "RedHeadDuck.h"
#include "Quack.h"
#include "FlyWithWings.h"
#include "LaysEggsBroody.h"
RedHeadDuck::RedHeadDuck()
{
   quackBehavior = new Quack();
   flyBehavior = new FlyWithWings();
   layeggs = new LaysEggsBroody();
}

void RedHeadDuck::display()
{
   std::cout << "I’m a real redheaded duck" << std::endl;
}
