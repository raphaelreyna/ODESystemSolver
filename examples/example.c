#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#import "../headers/NumericalMethods.h"
#import "../headers/VectorMatrixAlgebra.h"

int main()
{
  // Initial conditions with y_0(0)=1 and y_1(0)=-1.
  Vector *yBar = makeVector(2, 1.0, -1.0);
  // Matrix describing the system. {{-2,1},{1,-2}}.
  Vector *row0 = makeVector(2, -2.0, 1.0);
  Vector *row1= makeVector(2, 1.0, -2.0);
  Matrix *m = makeMatrix(2, row0, row1);

  // Create context for solving ODE system from t = 0 to t = 1.
  // Delta t is set to 0.00001.
  ODEContext *context = makeODEContext(0.00001, 2, m, yBar, 0.0, 1.0);

  // Compute solution using Euler's method.
  eulersMethod(context);

  // Print results.
  printf("Used %lu steps to solve the ODE system.\n", context->steps);
  printf("y_0(1) = %f\n", yBar->elements[0]);
  printf("y_1(1) = %f\n", yBar->elements[1]);

  // Clean up.
  freeODEContext(context);
  destroyVector(yBar);
  destroyMatrix(m);

  //Everything went ok :)
  return 0;
}
