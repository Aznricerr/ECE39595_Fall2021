#include <iostream>
#include "MallardDuck.h"
#include "Quack.h"
#include "FlyWithWings.h"

MallardDuck::MallardDuck( ) {
   quackBehavior = new Quack( );
   flyBehavior = new FlyWithWings( );
}

void MallardDuck::display( ) {
   std::cout << "I’m a real mallard duck" << std::endl;
}
