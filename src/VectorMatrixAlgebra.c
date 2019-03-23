#include "../headers/VectorMatrixAlgebra.h"
#include "../headers/NumericalMethods.h"
#include <stdarg.h>

void
vCopy(Vector * from,
      Vector * to){
  for (unsigned long k = 0; k < from->size; k++){
    to->elements[k] = from->elements[k];
  }
}

void
vAdd(Vector *a,
     Vector *b){
  for (unsigned long k = 0; k < a->size; k++){
    a->elements[k] += b->elements[k];
  }
}

void
vMult(Vector *a,
      double r) {
  for (unsigned long k = 0; k < a->size; k++){
    a->elements[k] *= r;
  }
}

double
vDot(Vector *a,
     Vector *b){
  double total = 0;
  for (unsigned long k = 0; k < a->size; k++){
    total += (a->elements[k])*(b->elements[k]);
  }
  return total;
}

void
vMatMul(Matrix * m,
        Vector * a,
        Vector * dirtyVector){
  for (unsigned long k = 0; k < a->size; k++){
    Vector *row = (m->rows[k]);
    dirtyVector->elements[k] = vDot(a, row);
  }
  vCopy(dirtyVector, a);
}

Vector*
makeVector(int dimension,
           ...){
  Vector* v = malloc(sizeof(Vector));
  v->elements = malloc(sizeof(double)*dimension);
  v->size = dimension;
  va_list valist;
  va_start(valist, dimension);
  for (int i = 0 ; i < dimension ; i++) {
    *(v->elements+i) = va_arg(valist, double);
  }
  va_end(valist);
  return v;
}

Matrix*
makeMatrix(int dimension,
           ...){
  Matrix* m = malloc(sizeof(Matrix));
  m->size = dimension;
  m->rows = malloc(sizeof(Vector*)*dimension);
  va_list valist;
  va_start(valist, dimension);

  for (int i = 0 ; i < dimension ; i ++){
    *(m->rows+i) = va_arg(valist, Vector*);
  }

  va_end(valist);
  return m;
}

void
destroyVector(Vector* v){
  free(v->elements);
  free(v);
}

void
destroyMatrix(Matrix* m) {
  for (int i = 0 ; i < m->size ; i++){
    Vector* row = *(m->rows+i);
    destroyVector(row);
  }
  free(m->rows);
  free(m);
}
