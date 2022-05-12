#include <iostream>
#include "Matrix.h"

Matrix::Matrix(int d1, int d2) : dim1Extent(d1), dim2Extent(d2)
{
   data = new double[d1 * d2];
}

double &Matrix::operator()(int r, int c)
{
   return *(this->data + r * dim1Extent + c);
}