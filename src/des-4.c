/* --------------------------------------------------------------------------------
#
#   Discrete Event Simultion: A First Course
#   Algorithms from Ch. 4
#   Sean Wu (slwu89@berkeley.edu)
#   January 2020
#
-------------------------------------------------------------------------------- */

#include "des-4.h"


/* --------------------------------------------------------------------------------
#   algorithm 4.1.1: Welford's one pass algorithm
-------------------------------------------------------------------------------- */

SEXP des_4_1_1_C(SEXP sampleR){

  int ntot = Rf_length(sampleR);
  double* x = REAL(sampleR);

  int n = 0;
  double xbar = 0.0;
  double v = 0.0;

  double d;
  for(int i=0; i<ntot; i++){
    n++;
    d = x[i] - xbar;    /* temporary variable */
    v = v + d * d * ((double)n - 1.) / (double)n;
    xbar = xbar + d / (double)n;
  }

  double s = sqrt(v / (double)n);

  /* build SEXP objects to return to R */
  SEXP out = PROTECT(Rf_allocVector(REALSXP,2));
  REAL(out)[0] = xbar;
  REAL(out)[1] = s;
  SEXP nms = PROTECT(Rf_allocVector(STRSXP,2));
  Rf_namesgets(out, nms);
  SET_STRING_ELT(nms, 0, Rf_mkChar("xbar"));
  SET_STRING_ELT(nms, 1, Rf_mkChar("s"));

  UNPROTECT(2);
  return out;
};
