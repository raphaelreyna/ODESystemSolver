#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <curses.h>
#import "../headers/NumericalMethods.h"
#import "../headers/VectorMatrixAlgebra.h"

int main()
{
  // Initial conditions with y_0(0)=1 and y_1(0)=1.
  Vector *yBar = makeVector(2, 1.0, -1.0);
  // Matrix describing the system. {{-2,1},{1,-2}}.
  Vector *row0 = makeVector(2, -2.0, 1.0);
  Vector *row1= makeVector(2, 1.0, -2.0);
  Matrix *m = makeMatrix(2, row0, row1);

  // Create context for solving ODE system from t = 0 to t = 1.
  // Delta t is set to 0.00001.
  ODEContext *context = makeODEContext(0.00001, 2, m, yBar, 0.0, 1.0);

  // Arrays for plot values of both functions.
  double * y1Vals = malloc(sizeof(double)*(context->steps));
  double * y2Vals = malloc(sizeof(double)*(context->steps));

  // Extreme values used to reshape solutions for plotting.
  double maximum = 0;
  double minimum = 0;

  for (unsigned long i = 0 ; i < context->steps ; i++) {
    // Update the solution.
    eulersMethodStep(context);

    // Capture the current solution.
    *(y1Vals+i) = yBar->elements[0];
    *(y2Vals+i) = yBar->elements[1];

    // Update extreme values by comparing to current values.
    if (*(y1Vals+i) > maximum){
      maximum = *(y1Vals+i);
    }
    if (*(y2Vals+i) > maximum){
      maximum = *(y2Vals+i);
    }
    if (*(y1Vals+i) < minimum){
      minimum = *(y1Vals+i);
    }
    if (*(y2Vals+i) < minimum){
      minimum = *(y2Vals+i);
    }
  }

  // Used to normalize solutions for plotting.
  double height = maximum - minimum;

  // Initialize curses.
  initscr();
  // Get dimensions of curses windows.
  int rows;
  int cols;
  getmaxyx(stdscr, rows, cols);

  // Reshape and plot.
  for (unsigned long i = 0 ; i < context->steps ; i++) {
    // Reshape solutions so they fit on screen.
    *(y1Vals+i) = ((double)cols)*(*(y1Vals+i) - minimum)/height;
    *(y2Vals+i) = ((double)cols)*(*(y2Vals+i) - minimum)/height;
    // Compute x-coordinate for point.
    int x = floor(context->epsilon*i*rows);
    // Put solution point on screen as character.
    mvprintw(cols-((int)*(y1Vals+i)), x, "1");
    mvprintw(cols-((int)*(y2Vals+i)), x, "2");
  }
  // Update curses window.
  refresh();
  // Wait for user to press key before exiting.
  getch();
  // Close curses.
  endwin();
  // Clean up.
  freeODEContext(context);
  destroyVector(yBar);
  destroyMatrix(m);
  // Everything went ok :)
  return 0;
}
