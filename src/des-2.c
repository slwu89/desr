/* --------------------------------------------------------------------------------
#
#   Discrete Event Simultion: A First Course
#   Algorithms from Ch. 2
#   Sean Wu (slwu89@berkeley.edu)
#   December 2019
#
-------------------------------------------------------------------------------- */

#include "des-2.h"


/* --------------------------------------------------------------------------------
#   algorithm 2.1.1: determine if multiplier relative to the prime modulus m
-------------------------------------------------------------------------------- */

SEXP des_2_1_1_C(SEXP aR, SEXP mR){

  int a = Rf_asInteger(aR);
  int m = Rf_asInteger(mR);

  int p = 1;
  int x = a;

  while(x != 1){
    // check every once in awhile in case m isn't a prime
    if(p % 100 == 0){
      R_CheckUserInterrupt();
    }
    p += 1;
    x = (a * x) % m; /* beware of a * x overflow */
  }

  int res;
  if(p == m - 1){
    res = 1;
  } else {
    res = 0;
  }

  return Rf_ScalarLogical(res);
};


/* --------------------------------------------------------------------------------
#   algorithm 2.1.2: given mod m and a full-period multiplier a, determine all other full-period multipliers
-------------------------------------------------------------------------------- */

SEXP des_2_1_2_C(SEXP aR, SEXP mR){

  int a = Rf_asInteger(aR);
  int m = Rf_asInteger(mR);

  /* temp output */
  int* mults = (int*)calloc(m,sizeof(int));
  int  mults_found = 0;

  int i = 1;
  int x = a;

  /* find the multipliers */
  while(x != 1){

    if(i % 100 == 0){
      R_CheckUserInterrupt();
    }

    SEXP gcd = gcd_C(Rf_ScalarInteger(i),Rf_ScalarInteger(m-1));
    if(Rf_asInteger(gcd) == 1){
      mults[mults_found] = x;
      mults_found++;
    }
    i++;
    x = (a * x) % m; /* beware of a * x overflow */

  }

  /* prepare output */
  SEXP mults2r = PROTECT(allocVector(INTSXP,mults_found));
  memcpy(INTEGER(mults2r),mults,sizeof(int)*mults_found);

  UNPROTECT(1);
  free(mults);
  return mults2r;
};


/* --------------------------------------------------------------------------------
#   algorithm 2.2.1: evaluate ax mod m without producing any integers larger than m-1
-------------------------------------------------------------------------------- */

SEXP des_2_2_1_C(SEXP xR, SEXP aR, SEXP mR){

  int x = Rf_asInteger(xR);
  int a = Rf_asInteger(aR);
  int m = Rf_asInteger(mR);

  int* factor = approx_factor(a,m);
  int q = factor[0];
  int r = factor[1];

  int t = a * (x % q) - r * (x / q); // t = gamma(x)
  free(factor);

  if(t > 0){
    return ScalarInteger(t); // delta(x) = 0
  } else {
    return ScalarInteger(t+m); // delta(x) = 1
  }
};

/* internal C version of 2.2.1 */
int g(const int x, const int a, const int m){

  int* factor = approx_factor(a,m);
  int q = factor[0];
  int r = factor[1];

  int t = a * (x % q) - r * (x / q); // t = gamma(x)
  free(factor);

  if(t > 0){
    return t; // delta(x) = 0
  } else {
    return t+m; // delta(x) = 1
  }
};


/* --------------------------------------------------------------------------------
#   algorithm 2.2.2: Given the prime modulus m and any associated full-period, modulus- compatible multiplier a the following algorithm generates all the full-period, modulus- compatible multipliers relative to m.
-------------------------------------------------------------------------------- */

SEXP des_2_2_2_C(SEXP aR, SEXP mR){

  int a = Rf_asInteger(aR);
  int m = Rf_asInteger(mR);

  /* set up storage for output */
  int mults_sz = (m - 1)/2; // there won't be more than this, but we check later on just in case
  int* mults_found = (int*)calloc(mults_sz,sizeof(int));
  int mults_i = 0;

  /* algorithm */
  int i = 1;
  int x = a;

  while(x != 1){

    if(i % 10 == 0){
      R_CheckUserInterrupt();
    }

    if((m % x < m / x) && (gcd(i,m-1) == 1)){
      /* x is a full-period modulus-compatible multiplier */
      if(mults_i > mults_sz){
        mults_found = (int*)realloc(mults_found,mults_sz*2*sizeof(int));
      }
      mults_found[mults_i] = x;
      mults_i++;
    }
    i++;
    x = g(x,a,m);
  }

  /* return output to R */
  SEXP output = PROTECT(Rf_allocVector(INTSXP,mults_i));
  memcpy(INTEGER(output),mults_found,sizeof(int)*mults_i);

  free(mults_found);
  UNPROTECT(1);
  return output;
};
