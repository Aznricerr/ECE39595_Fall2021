#include <iostream>
#include <cstdlib>
#include "Array2D.H"
#include <string>

// This constructor is delegated to by other constructors and does all of the
// allocation, showing an example of a delegating constructor..
Array2D::Array2D(int numR, int numC, char differentiator) : numRows(numR), numCols(numC)
{

   ary = new int *[numRows];
   for (int i = 0; i < numRows; i++)
   {
      ary[i] = new int[numCols];
      for (int j = 0; j < numCols; j++)
      {
         ary[i][j] = -1;
      }
   }
}

Array2D::Array2D(int numR, int numC) : Array2D(numR, numC, 'c')
{
   for (int i = 0; i < numRows; i++)
   {
      for (int j = 0; j < numCols; j++)
      {
         ary[i][j] = i;
      }
   }
}

Array2D::Array2D(int numR, int numC, int val) : Array2D(numR, numC, 'c')
{
   for (int i = 0; i < numRows; i++)
   {
      for (int j = 0; j < numCols; j++)
      {
         ary[i][j] = val;
      }
   }
}

//Array2D Copy Constructor
Array2D::Array2D(const Array2D &other)
{
   numRows = other.getNumRows();
   numCols = other.getNumCols();
   ary = new int *[numRows];
   for (int r = 0; r < numRows; r++)
   {
      ary[r] = new int[numCols];
      for (int c = 0; c < numCols; c++)
      {
         ary[r][c] = other.ary[r][c];
      }
   }
}
//Copy Constructor End

//Array2D& Operator =
Array2D &Array2D::operator=(Array2D &arr)
{
   deleteAry(this->ary);

   numCols = arr.getNumCols();
   numRows = arr.getNumRows();

   ary = new int *[numRows];
   for (int r = 0; r < numRows; r++)
   {
      ary[r] = new int[numCols];
      for (int c = 0; c < numCols; c++)
      {
         ary[r][c] = arr.ary[r][c];
      }
   }
   return *this;
}
//Array2D& operator = END

//== operator
bool Array2D::operator==(Array2D &arr)
{
   if (!(this->sameSize(arr)))
   {
      return false;
   }
   else
   {
      for (int r = 0; r < numRows; r++)
      {
         for (int c = 0; c < numCols; c++)
         {
            if (ary[r][c] != arr.ary[r][c])
            {
               return false;
            }
         }
      }
   }
   return true;
}
//== operator END

//Matrix Mult Op
Array2D &Array2D::operator*(Array2D &arr)
{
   if (numCols != arr.getNumRows())
   {
      Array2D *temp = new Array2D(numRows, numCols, -1);
      return *temp;
   }
   Array2D *ret = new Array2D(numRows, arr.getNumCols(), 0);
   for (int r1 = 0; r1 < numRows; r1++)
   {
      for (int c2 = 0; c2 < arr.getNumCols(); c2++)
      {
         for (int r2 = 0; r2 < arr.getNumRows(); r2++)
         {
            ret->ary[r1][c2] += this->ary[r1][r2] * arr.ary[r2][c2];
         }
      }
   }
   return *ret;
}
//mult op END

//output txt file funt
std::ostream &operator<<(std::ostream &os, Array2D &arr)
{
   for (int r = 0; r < arr.getNumRows(); r++)
   {
      for (int c = 0; c < arr.getNumCols(); c++)
      {
         os << std::to_string(arr(r, c)) + " ";
      }
      os << std::endl;
   }
   return os;
}
//to txt END

int &Array2D::operator()(int row, int col)
{
   return ary[row][col];
}

int Array2D::operator()(int row, int col) const
{
   return ary[row][col];
}

bool Array2D::sameSize(const Array2D &other) const
{
   return (numRows == other.getNumRows() && numCols == other.getNumCols());
}

//Destructor Array2D
Array2D::~Array2D()
{
   deleteAry(this->ary);
}
//Destructor End

void Array2D::deleteAry(int **ary)
{
   for (int i = 0; i < numRows; i++)
   {
      delete[] ary[i];
   }
   delete[] ary;
}

int Array2D::getNumRows() const
{
   return numRows;
}
int Array2D::getNumCols() const
{
   return numCols;
}