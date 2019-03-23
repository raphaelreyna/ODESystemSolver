#include <stdio.h>
#include <stdlib.h>
#import "../headers/NumericalMethods.h"
#import "../headers/VectorMatrixAlgebra.h"

int main(int argc, const char * argv[])
{
  Vector *yBar = makeVector(2, 1.0, 1.0);

  Vector *row0 = makeVector(2, 3.0, -5.0);

  Vector *row1= makeVector(2, 2.0, 0.7);

  Matrix *m = makeMatrix(2, row0, row1);

  ODEContext *context = makeODEContext(0.00001, 2, m, yBar, 0.0, 1.0);
  eulersMethod(context);
  printf("Steps taken: %lu \n", context->steps);
  printf("Value of f1: %f, Value of f2: %f\n", yBar->elements[0], yBar->elements[1]);
  freeODEContext(context);
  destroyVector(yBar);
  destroyMatrix(m);

  return 0;
}
