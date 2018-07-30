// 1. A C++ function cannot directly return an array. It can however return the address of the array and the information within that array can be used.
// If an array needs to be returned, a third parameter can be created and that third parameter can be printed. An array is essentially a chunck of memory,
// and that itself cannot be returned. An array is a constant pointer, so it can never be changed.

#include <iostream>
#include <cstdlib>  
#include <time.h>

const int rows = 5;
const int cols = 5;

void printMatrix(int matrix[rows][cols])
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++) std::cout << matrix[i][j] << " "; 
    std::cout << "\n"; 
  }
}

// The reason that it is mod'd 10 is because I want one digit numbers inside the matrix so there is no problem of offsets.
void fillMatrix(int matrix[rows][cols])
{
  srand(time(NULL));
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) matrix[i][j] = rand() % 10;  
}

void transposeMatrix(int matrix[rows][cols])
{
  for (int i = 0; i < rows; i++)
    for (int j = i; j < cols; j++) 
    {
      int temp = matrix[i][j];
      matrix[i][j] = matrix[j][i];
      matrix[j][i] = temp;
    }
}

void product(int prod1[rows][cols], int prod2[rows][cols], int result[rows][cols])
{
  int sum = 0;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      sum = 0;
      for(int k = 0; k < rows; k++) sum += prod1[i][k] * prod2[k][j];
      result[i][j] = sum;
    }
  }
}

int sumProd(int prod1[rows][cols], int prod2[rows][cols], int i, int j, int k)
{
  if(k < 0) return 0;
  return prod1[i][k] * prod2[k][j] + sumProd(prod1, prod2, i, j, k - 1);
}

void recProduct(int prod1[rows][cols], int prod2[rows][cols], int i, int j, int result[rows][cols])
{
  int sum = 0, k = 4;
  result[i][j] = sumProd(prod1, prod2, i, j, k);
  if(i > 0)
  {
    if(j > 0) recProduct(prod1, prod2, i, j - 1, result);
    recProduct(prod1, prod2, i - 1, j, result);
  }
}

void fillPtrMatrix(int** matrix)
{
  srand(time(NULL));
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) *(*(matrix + i) + j) = rand() % 10; 
}

void transposePtrMatrix(int** matrix)
{
  for (int i = 0; i < rows; i++)
    for (int j = i; j < cols; j++) 
    {
      int temp = *(*(matrix + i) + j);
      *(*(matrix + i) + j) = matrix[j][i];
      *(*(matrix + j) + i) = temp;
    }
}


void printPtrMatrix(int** matrix)
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++) std::cout << *(*(matrix + i) + j) << " "; 
    std::cout << "\n"; 
  }
}

void fillTest1D(int matrix[rows * cols])
{
  srand(time(NULL));
  for (int i = 0; i < 25; i++) matrix[i] = rand() % 10; 
}

void printTest1D(int matrix[rows * cols])
{
  srand(time(NULL));
  for (int i = 0; i < 25; i++)
  {
    std::cout << matrix[i] << " ";
    if((i+1) % 5 == 0) std::cout << "\n";
  }
}

int main() 
{
  int test[rows][cols];
  int prod[rows][cols];
  int recProd[rows][cols];
  int** ptrTest = new int*[rows];
  for (int i = 0; i < rows; i++) *(ptrTest+i) = new int[cols];
  int test1D[rows * cols];

  std::cout << "fillMatrix()\n";
  fillMatrix(test);
  printMatrix(test);
  std::cout << "\n";
 
  std::cout << "transposeMatrix()\n";
  transposeMatrix(test);
  printMatrix(test);
  std::cout << "\n";

  std::cout << "product()\n";
  product(test, test, prod); 
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++) std::cout << prod[i][j] << " "; 
    std::cout << "\n"; 
  }
  std::cout << "\n";

  std::cout << "recProduct()\n"; 
  // rows - 1 = 4
  recProduct(test, test, 4, 4, recProd);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++) std::cout << recProd[i][j] << " "; 
    std::cout << "\n"; 
  }
  std::cout << "\n"; 

  std::cout << "fillPtrMatrix()\n"; 
  fillPtrMatrix(ptrTest);
  printPtrMatrix(ptrTest);
  std::cout << "\n"; 

  std::cout << "transposePtrMatrix()\n"; 
  transposePtrMatrix(ptrTest);
  printPtrMatrix(ptrTest);
  std::cout << "\n"; 

  fillTest1D(test1D);
  std::cout << "Printing 1D Array\n";
  for(int i = 0; i < rows * cols; i++) std::cout << test1D[i] << " ";
  std::cout << "\n\nPrinting Matrix\n";
  printTest1D(test1D);

  return 0;
}

