/* --------------------------------------------------------------------------------
#
#   Discrete Event Simultion: A First Course
#   Algorithms from Ch. 1
#   Sean Wu (slwu89@berkeley.edu)
#   December 2019
#
-------------------------------------------------------------------------------- */

#include "des-1.h"

/* algorithm 1.2.1: calculate delays under FIFO with finite capacity */
SEXP des1_2_1(SEXP arrivals, SEXP services){
  int n = LENGTH(arrivals);
  if(LENGTH(services) != n){
    error("'arrivals' and 'services' vectors must be the same length\n");
  }

  double* c = malloc(n * sizeof(double));
  int i = 0;

  double* a = REAL(arrivals);
  double* s = REAL(services);

  while(i < n){
    i++;


  }

  free(c);
};
