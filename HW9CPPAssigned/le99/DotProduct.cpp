#include <iostream>
#include <string>
#include <stdlib.h>
#include "DotProduct.h"

DotProduct::DotProduct()
{
    DotProduct(0);
}

DotProduct::DotProduct(int numElements) : length(numElements)
{
    dProd = 0;
    arrA = new int[length];
    arrB = new int[length];
    for (int i = 0; i < length; i++)
    {
        arrA[i] = rand() % 100;
        arrB[i] = rand() % 100;
    }
}

std::ostream &operator<<(std::ostream &os, const DotProduct dp)
{
    os << "inner product on arrays of length " << dp.length << ", result is " << dp.dProd << "\n\n";
    return os;
}

void DotProduct::execute()
{
    for (int i = 0; i < length; i++)
    {
        dProd += arrA[i] * arrB[i];
    }
}

void DotProduct::identify()
{
    std::cout << *this;
}