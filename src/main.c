#include <stdio.h>
#include <stdlib.h>
#import "../headers/NumericalMethods.h"

int main(int argc, const char * argv[])
{
  Vector *yBar = malloc(sizeof(Vector));
  yBar->size = 2;
  yBar->elements = malloc(sizeof(double)*2);
  *(yBar->elements) = 1.0;
  *(yBar->elements+1) = 1.0;

  Vector *row0 = malloc(sizeof(Vector));
  row0->size = 2;
  row0->elements = malloc(sizeof(double)*2);
  *(row0->elements) = 3.0;
  *(row0->elements+1) = -5.0;

  Vector *row1= malloc(sizeof(Vector));
  row1->size = 2;
  row1->elements = malloc(sizeof(double)*2);
  *(row1->elements) = 2.0;
  *(row1->elements+1) = 0.7;

  Matrix *m = malloc(sizeof(Matrix));
  m->size = 2;
  m->rows = malloc(sizeof(Vector*)*2);
  *(m->rows) = row0;
  *(m->rows+1) = row1;

  ODEContext *context = makeODEContext(0.00001, 2, m, yBar, 0.0, 1.0);
  eulersMethod(context);
  printf("Steps taken: %lu \n", context->steps);
  printf("Value of f1: %f, Value of f2: %f\n", yBar->elements[0], yBar->elements[1]);
  freeODEContext(context);
  free(yBar->elements);
  free(yBar);
  free(row0->elements);
  free(row0);
  free(row1->elements);
  free(row1);
  free(m->rows);
  free(m);
}
