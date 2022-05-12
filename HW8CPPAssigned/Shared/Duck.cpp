#include <iostream>
#include "Duck.h"

Duck::Duck() {}

void Duck::swim()
{
   std::cout << "All ducks float" << std::endl;
}

void Duck::performQuack()
{
   quackBehavior->quack();
}

void Duck::performFly()
{
   flyBehavior->fly();
}

void Duck::setFlyBehavior(FlyBehavior *fb)
{
   std::shared_ptr<FlyBehavior> flyBehavior = std::shared_ptr<FlyBehavior>(fb);
}

void Duck::setQuackBehavior(QuackBehavior *qb)
{
   std::shared_ptr<QuackBehavior> quackBehavior = std::shared_ptr<QuackBehavior>(qb);
}
