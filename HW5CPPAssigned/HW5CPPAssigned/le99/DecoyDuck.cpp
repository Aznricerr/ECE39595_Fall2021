#include <iostream>
#include "DecoyDuck.h"
#include "FlyNoWay.h"
#include "MuteQuack.h"
#include "LaysEggsBroody.h"

DecoyDuck::DecoyDuck()
{
   flyBehavior = new FlyNoWay();
   quackBehavior = new MuteQuack();
   layeggs = new LaysEggsBroody();
}

void DecoyDuck::display()
{
   std::cout << "I’m a decoy duck" << std::endl;
}
