#ifndef ARRAY2D_H_
#define ARRAY2D_H_
#include <iostream>
class Array2D
{

public:
   Array2D(int numR, int numC);
   Array2D(int numR, int numC, int val);
   Array2D(const Array2D &other);

   virtual int &operator()(int row, int col);
   virtual int operator()(int row, int col) const;

   //Functions tobe implemented
   ~Array2D();
   virtual int getNumRows() const;
   virtual int getNumCols() const;
   virtual Array2D &operator=(Array2D &arr);
   virtual bool operator==(Array2D &arr);
   virtual Array2D &operator*(Array2D &arr);

private:
   Array2D(int numR, int numC, char differentiator);
   void deleteAry(int **ary);
   bool sameSize(const Array2D &other) const;
   int **ary;
   int numRows;
   int numCols;
};
std::ostream &operator<<(std::ostream &os, Array2D &arr);
#endif /* ARRAY2D_H_ */
