/* --------------------------------------------------------------------------------
#
#   Discrete Event Simultion: A First Course
#   Appendices, extras, and helper functions
#   Sean Wu (slwu89@berkeley.edu)
#   December 2019
#
-------------------------------------------------------------------------------- */

#include "des-errata.h"


/* --------------------------------------------------------------------------------
#   gcd via Euclidean algorithm
-------------------------------------------------------------------------------- */

SEXP gcd_C(SEXP aR, SEXP bR){

  int a = Rf_asInteger(aR);
  int b = Rf_asInteger(bR);

  if(a < 0 || b < 0){
    Rf_error("both 'a' and 'b' should be positive integers");
  }

  int r = a % b;
  while(r > 0){
    a = b;
    b = r;
    r = a % b;
  }
  return Rf_ScalarInteger(b);
}


/* --------------------------------------------------------------------------------
#   sieve of Eratosthenes
-------------------------------------------------------------------------------- */

SEXP sieve_C(SEXP NR){

  int N = Rf_asInteger(NR);

  if(N <= 2){
    Rf_error("'N' should be greater than 2");
  }

  int n;
  int s; // step index

  /* initialize the sieve */
  int prime[N+1];
  prime[0] = 0;
  prime[1] = 0;
  for(n = 2; n <= N; n++){
    prime[n] = 1;
  }

  /* run the sieve */
  int sqrtN = (int)sqrt((double)N);
  for(n = 2; n <= sqrtN; n++){
    if(prime[n]){
      for(s = 2; s <= (N/n); s++){
        prime[s*n] = 0;
      }
    }
  }

  /* number of primes (to fill output) */
  int np = 0;
  for(n=0; n<=N; n++){
    if(prime[n]){
      np++;
    }
  }

  SEXP output = PROTECT(Rf_allocVector(INTSXP, np));
  int* out_ptr = INTEGER(output);
  int out_i = 0;
  for(n = 0; n <= N; n++){
    if(prime[n]){
      out_ptr[out_i] = n;
      out_i++;
    }
  }

  UNPROTECT(1);
  return output;
};


/* --------------------------------------------------------------------------------
#   approximate factorization
-------------------------------------------------------------------------------- */

SEXP approx_factor_C(SEXP aR, SEXP MR){
  
  int a = Rf_asInteger(aR);
  int m = Rf_asInteger(MR);
  int q = (int)floor((double)m/(double)a);
  int r = m % a;

  SEXP output = PROTECT(Rf_allocVector(INTSXP,2));

  INTEGER(output)[0] = q;
  INTEGER(output)[1] = r;

  SEXP nms = PROTECT(Rf_allocVector(STRSXP, 2));
  Rf_namesgets(output, nms);
  SET_STRING_ELT(nms, 0, mkChar("q"));
  SET_STRING_ELT(nms, 1, mkChar("r"));

  UNPROTECT(2);
  return output;
};
