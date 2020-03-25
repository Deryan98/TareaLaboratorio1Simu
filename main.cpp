#include <iostream>
#include "math_tools.h"
#include "display_tools.h"

int main(void)
{
  Matrix example_matrix, inverse_matrix;

  zeroes(example_matrix, 3);

  //Ingresando datos a la matriz
  example_matrix.at(0).at(0) = 2;
  example_matrix.at(0).at(1) = 2;
  example_matrix.at(0).at(2) = 3;
  example_matrix.at(1).at(0) = 4;
  example_matrix.at(1).at(1) = 5;
  example_matrix.at(1).at(2) = 6;
  example_matrix.at(2).at(0) = 7;
  example_matrix.at(2).at(1) = 8;
  example_matrix.at(2).at(2) = 9;

  //calculando matriz inversa
  inverse(example_matrix, inverse_matrix);

  cout << "Mostrando Matriz Inversa" << endl;

  showMatrix(inverse_matrix);

  return 0;
}