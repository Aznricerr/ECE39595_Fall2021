#include "Duck.h"
#include "RedHeadDuck.h"
#include "MallardDuck.h"
#include "DecoyDuck.h"
#include "FlyNoWay.h"
#include <memory>

int main(int argc, char *argv[])
{
   std::unique_ptr<Duck> red = std::unique_ptr<Duck>(new RedHeadDuck());
   std::unique_ptr<Duck> mallard = std::unique_ptr<Duck>(new MallardDuck());
   std::unique_ptr<Duck> decoy = std::unique_ptr<Duck>(new DecoyDuck());

   red->performQuack();
   red->performFly();
   red->swim();
   red->setFlyBehavior(new FlyNoWay());
   red->performFly();

   decoy->performFly();
}
