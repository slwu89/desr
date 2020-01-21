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


/* --------------------------------------------------------------------------------
#   algorithm 4.2.1: discrete data histrogram
-------------------------------------------------------------------------------- */

SEXP des_4_2_1_C(SEXP aR, SEXP bR, SEXP dataR){

  int a = Rf_asInteger(aR);
  int b = Rf_asInteger(bR);
  int ntot = Rf_length(dataR);
  int* data = INTEGER(dataR);

  SEXP count_r = PROTECT(Rf_allocVector(INTSXP,b-a+1));
  int* count = INTEGER(count_r);
  memset(count,0,(b-a+1)*sizeof(int));
  int n, x;

  int out_lo = 0;
  int out_hi = 0;

  for(n=0; n<ntot; n++){
    x = data[n];
    if((a <= x) && (x <= b)){
      count[x-a]++;
    } else if(a > x){
      out_lo++;
    } else {
      out_hi++;
    }
  }

  SEXP out = PROTECT(Rf_allocVector(VECSXP,3));
  SET_VECTOR_ELT(out,0,count_r);
  SET_VECTOR_ELT(out,1,Rf_ScalarInteger(out_lo));
  SET_VECTOR_ELT(out,2,Rf_ScalarInteger(out_hi));

  SEXP names = PROTECT(Rf_allocVector(STRSXP,3));
  SET_STRING_ELT(names,0,Rf_mkChar("count"));
  SET_STRING_ELT(names,1,Rf_mkChar("outliers_lo"));
  SET_STRING_ELT(names,2,Rf_mkChar("outliers_hi"));

  Rf_namesgets(out,names);
  UNPROTECT(3);
  return out; /* f(x) is (count[x−a] / n) */
};
