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
   flyBehavior = std::unique_ptr<FlyBehavior>(fb);
}

void Duck::setQuackBehavior(QuackBehavior *qb)
{
   quackBehavior = std::unique_ptr<QuackBehavior>(qb);
}
