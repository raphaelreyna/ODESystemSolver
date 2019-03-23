#ifndef NumericalMethods_h
#define NumericalMethods_h
#import <stdlib.h>
#import "VectorMatrixAlgebra.h"

typedef struct ODEContexts {
  Vector *yBar;
  Vector *yBarPrime;
  Vector *dirtyVector;
  Matrix *ODESystem;
  double epsilon;
  int systemSize;
  unsigned long steps;
  short done;
} ODEContext;

ODEContext *
makeODEContext(double eps,
               int size,
               Matrix *odeSystem,
               Vector *yBar,
               double a,
               double b);

void
eulersMethodStep(ODEContext * context);

void
eulersMethod(ODEContext * context);

void
freeODEContext(ODEContext * context);
#endif
