#ifndef NumericalMethods_h
#define NumericalMethods_h

typedef struct ODEContext {
    double *approximations;
    double *aux_memory;
    double *(*ODE)(double x, double *y, double *dV);
    double epsilon;
    int systemSize;
} ODEContext;

ODEContext *makeODEContext(double epsilon, int size, double *initCondsVec, double *(*ODE)(double x, double *y, double *dV));

void eulersMethod(ODEContext *context, double a, double b);
void secantMethod(double (*f)(double), double *x_0, double *x_1, double epsilon);
void bisectionMethod(double (*f)(double), double *xa, double *xb, double epsilon);


#endif
