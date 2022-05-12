#include <iostream>
#include <string>
#include "Command.h"

class DotProduct : public Command
{
private:
    int *arrA;
    int *arrB;
    int length;
    double dProd;

public:
    DotProduct();
    DotProduct(int numElements);
    void execute();
    void identify();

    friend std::ostream &operator<<(std::ostream &os, const DotProduct dp);
};