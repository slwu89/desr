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
SEXP des1_2_1_C(SEXP arrivals, SEXP services){
  int n = LENGTH(arrivals);
  if(LENGTH(services) != n){
    error("'arrivals' and 'services' vectors must be the same length\n");
  }

  /* vector of service completions (departures) */
  double* c = calloc(n+1,sizeof(double));
  c[0] = 0.;

  /* vector of arrivals (a) and services times (s) */
  double* a = calloc(n+1,sizeof(double));
  double* s = calloc(n+1,sizeof(double));

  memcpy(a+1,REAL(arrivals),sizeof(double)*n);
  memcpy(s+1,REAL(services),sizeof(double)*n);

  /* departure times (the output) */
  SEXP d = PROTECT(allocVector(REALSXP,n));
  double* d_ptr = REAL(d);

  int i = 0;

  while(i < n){

    i++;
    double a_i = a[i];

    if(a_i < c[i-1]){
      /* calculate delay for job i */
      d_ptr[i-1] = c[i-1] - a_i;
    } else {
      /* job i has no delay */
      d_ptr[i-1] = 0.;
    }

    /* calculate departure time for job i */
    c[i] = a_i + d_ptr[i-1] + s[i];
  }

  /* free memory/unprotect and return */
  free(c);
  free(a);
  free(s);
  UNPROTECT(1);

  return d;
};
