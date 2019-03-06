#include <stdio.h>
#include <stdlib.h>
#import "../headers/NumericalMethods.h"

ODEContext *makeODEContext(double eps, int size, double *initCondsVec, double *(*ODE)(double x, double *y, double *dV)){
    ODEContext *context = malloc(sizeof(ODEContext));
    if (context){
        double *solutionVector = malloc(sizeof(double)*size);
        double *aux_mem = malloc(sizeof(double)*size);
        context->approximations = solutionVector;
        context->aux_memory = aux_mem;
        context->ODE = ODE;
        context->systemSize = size;
        context->epsilon = eps;
        for (int i = 0; i < size; i++) {
            solutionVector[i] = initCondsVec[i];
        }
        return context;
    }
    return NULL;
}

void eulersMethod(ODEContext *c, double a, double b){
    //get pointers to things in the context
    double *approxVec = c->approximations;
    double *aux_mem = c->aux_memory;
    double eps = c->epsilon;
    int size = c->systemSize;
    double *(*ode)(double, double*, double*) = c->ODE;

    //compute the step-size h
    double h = (b-a)*eps;
    //compute number of steps to take
    int n = (b-a)/eps;

    for (int k = 0; k <= n; k++){ //time step loop
        double t = a + k*h; //update time step
        for (int i = 0; i < size; i++) { //iterates the solver method over the solution vector.
            approxVec[i] = approxVec[i] + h*(ode(t, approxVec, aux_mem)[i]); //eulers method for a vector.
            if (i == 0) {
                printf("%f\n", approxVec[i]);
            }
        }
    }
}
