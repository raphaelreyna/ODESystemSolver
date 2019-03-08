#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#import "../headers/NumericalMethods.h"

void vCopy(Vector *from, Vector *to){
  for (unsigned long k = 0; k < from->size; k++){
    to->elements[k] = from->elements[k];
  }
}

void vAdd(Vector *a, Vector *b){
  for (unsigned long k = 0; k < a->size; k++){
    a->elements[k] += b->elements[k];
  }
}

void vMult(Vector *a, double r) {
  for (unsigned long k = 0; k < a->size; k++){
    a->elements[k] *= r;
  }
}

double vDot(Vector *a, Vector *b){
  double total = 0;
  for (unsigned long k = 0; k < a->size; k++){
    total += (a->elements[k])*(b->elements[k]);
  }
  return total;
}

void vMatMul(ODEContext* context, Matrix *m, Vector *a){
  for (unsigned long k = 0; k < a->size; k++){
    Vector *row = (m->rows[k]);
    context->dirtyVector->elements[k] = vDot(a, row);
  }
  vCopy(context->dirtyVector, a);
}

ODEContext *makeODEContext(double eps, int size, Matrix *odeSystem, Vector *yBar, double a, double b){
    ODEContext *context = malloc(sizeof(ODEContext));
    if (context){
      context->yBar = yBar;
      context->yBarPrime = malloc(sizeof(Vector));
      context->yBarPrime->elements = malloc(sizeof(double)*size);
      context->yBarPrime->size = size;
      context->dirtyVector = malloc(sizeof(Vector));
      context->dirtyVector->elements = malloc(sizeof(double)*size);
      context->dirtyVector->size = size;
      context->ODESystem = odeSystem;
      context->epsilon = eps;
      context->systemSize = size;
      context->steps = (unsigned long)floor((b-a)/eps);
      context->done = 0;
      return context;
    }
    return NULL;
}

void freeODEContext(ODEContext* context){
  free(context->yBarPrime->elements);
  free(context->yBarPrime);
  free(context->dirtyVector->elements);
  free(context->dirtyVector);
  free(context);
}

void eulersMethodStep(ODEContext *context){
  if (context->done == 1){
    return;
  }
  vCopy(context->yBar, context->yBarPrime);
  vMatMul(context, context->ODESystem, context->yBarPrime);
  vMult(context->yBarPrime, context->epsilon);
  vAdd(context->yBar, context->yBarPrime);
}

void eulersMethod(ODEContext *context){
  for (unsigned long k = 0; k < context->steps; k++){
    eulersMethodStep(context);
  }
  context->done = 1;
}
