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
