#ifndef VectorMatrixAlgebra_h
#define VectorMatrixAlgebra_h
#import <stdlib.h>
#import <stdarg.h>

typedef struct Vectors {
  size_t size;
  double *elements;
} Vector;

typedef struct Matrices {
  size_t size;
  Vector **rows;
} Matrix;

void
vCopy(Vector * a,
      Vector * b);

void
vAdd(Vector * a,
     Vector * b);

void
vMult(Vector * a,
      double r);

double
vDot(Vector * a,
     Vector * b);

void
vMatMul(Matrix * m,
        Vector * a,
        Vector * dirtyVector);

Vector *
makeVector(int dimension,
           ...); // Variadic parameters are typed double

Matrix *
makeMatrix(int dimension,
           ...); // Variadic parameters are typed Vector*

void
destroyVector(Vector * v);

void
destroyMatrix(Matrix * m);

#endif
