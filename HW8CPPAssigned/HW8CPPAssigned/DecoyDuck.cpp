#include <iostream>
#include "DecoyDuck.h"
#include "FlyNoWay.h"
#include "MuteQuack.h"

DecoyDuck::DecoyDuck( ) {
   flyBehavior = new FlyNoWay( );
   quackBehavior = new MuteQuack( );
}

void DecoyDuck::display( ) {
   std::cout << "I’m a decoy duck" << std::endl;
}
