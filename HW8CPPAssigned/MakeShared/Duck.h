#ifndef DUCK_H_
#define DUCK_H_
#include "QuackBehavior.h"
#include "FlyBehavior.h"
#include <memory>

class Duck
{
public:
   Duck();
   virtual void setFlyBehavior(FlyBehavior *);
   virtual void setQuackBehavior(QuackBehavior *);
   virtual void performQuack();
   virtual void performFly();
   virtual void swim();
   virtual void display() = 0;

protected:
   std::shared_ptr<QuackBehavior> quackBehavior;
   std::shared_ptr<FlyBehavior> flyBehavior;
};
#endif /* DUCK_H_ */
