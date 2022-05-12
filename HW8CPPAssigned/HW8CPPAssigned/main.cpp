#include "Duck.h"
#include "RedHeadDuck.h"
#include "MallardDuck.h"
#include "DecoyDuck.h"
#include "FlyNoWay.h"
int main(int argc, char *argv[]) {
   Duck* red = new RedHeadDuck( );
   Duck* mallard = new MallardDuck( );
   Duck* decoy = new DecoyDuck( );

   red->performQuack( );
   red->performFly( );
   red->swim( );
   red->setFlyBehavior(new FlyNoWay( ));
   red->performFly( );

   decoy->performFly( );
}
