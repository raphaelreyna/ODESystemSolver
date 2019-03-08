#ifndef NumericalMethods_h
#define NumericalMethods_h
#import <stdlib.h>

typedef struct Vectors {
  size_t size;
  double *elements;
} Vector;

typedef struct Matrices {
  size_t size;
  Vector **rows;
} Matrix;

typedef struct ODEContext {
  Vector *yBar;
  Vector *yBarPrime;
  Vector *dirtyVector;
  Matrix *ODESystem;
  double epsilon;
  int systemSize;
  unsigned long steps;
  short done;
} ODEContext;

ODEContext *makeODEContext(double eps, int size, Matrix *odeSystem, Vector *yBar, double a, double b);

void eulersMethodStep(ODEContext *context);
void eulersMethod(ODEContext *context);
#endif
