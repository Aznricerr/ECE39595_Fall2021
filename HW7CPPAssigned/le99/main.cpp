#include <iostream>
#include "Int.h"
#include "Node.h"
#include "Float.h"

int main(int argc, char **args)
{
   const int values[]{5, 1, 7, 15};
   const double value[]{5.1, 1.1, 7.1, 15.1};

   Node<Int> *rootInt = new Node<Int>(Int(10));

   for (int i = 0; i < 4; i++)
   {
      rootInt->insertNode(Int(values[i]));
   }

   rootInt->print();
   std::cout << std::endl;

   Node<double> *rootDouble = new Node<double>(10.0);
   for (int i = 0; i < 4; i++)
   {
      rootDouble->insertNode((double)value[i]);
   }

   rootDouble->print();
   std::cout << std::endl;

   Node<Float> *rootFloot = new Node<Float>(Float(10.0));
   for (int i = 0; i < 4; i++)
   {
      rootFloot->insertNode(Float(value[i]));
   }

   rootFloot->print();
   std::cout << std::endl;
}
