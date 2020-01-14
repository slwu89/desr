/* --------------------------------------------------------------------------------
#
#   Discrete Event Simultion: A First Course
#   Algorithms from Ch. 2
#   Sean Wu (slwu89@berkeley.edu)
#   December 2019
#
-------------------------------------------------------------------------------- */

#include "des-2.h"

#include "slist.h"


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


/* --------------------------------------------------------------------------------
#   algorithm 2.5.1 Given the state transition function g(·) and initial state x0, this algorithm determines the fundamental pair (s, p)
-------------------------------------------------------------------------------- */

SEXP des_2_5_1_C(SEXP g, SEXP x0R, SEXP rho){

  if(!Rf_isFunction(g)){
    Rf_error("'g' should be a function");
  }
  if(!Rf_isEnvironment(rho)){
    Rf_error("'rho' should be an environment");
  }

  int x0 = Rf_asInteger(x0R);
  int t = 0;
  int s = 0;


  /* R function call and its argument */
  SEXP R_fcall, x;
  PROTECT(R_fcall = lang2(g, R_NilValue));
  PROTECT(x = allocVector(INTSXP,1));

  /* initialize the list x */
  int_slist x_lst;
  init_int_slist(&x_lst);
  add_int_slist(&x_lst,x0);

  int x_tp1;

  /* while no match found */
  while(s == t){

    /* evaluate x_{t+1} = g(x_{t}) */
    INTEGER(x)[0] = x_lst.tail->value;
    SETCADR(R_fcall,x);

    /* add a state to the list */
    x_tp1 = Rf_asInteger(Rf_eval(R_fcall,rho));
    add_int_slist(&x_lst,x_tp1);
    t++;

    /* traverse the list */
    s = 0;
    int_node* x_s = x_lst.head;
    while(x_s->value != x_tp1){
      if(x_s->next != NULL){
        x_s = x_s->next;
        s++;
      } else {
        break;
      }
    }
  }

  /* period is the distance between matches */
  int p = t - s;

  /* build SEXP objects to return to R */
  SEXP out = PROTECT(Rf_allocVector(INTSXP,2));
  INTEGER(out)[0] = s;
  INTEGER(out)[1] = p;
  SEXP nms = PROTECT(Rf_allocVector(STRSXP,2));
  Rf_namesgets(out, nms);
  SET_STRING_ELT(nms, 0, Rf_mkChar("s"));
  SET_STRING_ELT(nms, 1, Rf_mkChar("p"));

  /* clean up after ourselves */
  free_int_slist(&x_lst);
  UNPROTECT(2);
  return out;
};


/* --------------------------------------------------------------------------------
#   Lehman random number generator via external ptr
-------------------------------------------------------------------------------- */

/* code to free the memory when the pointer is garbage collected by R */
void free_lrng_C(SEXP ptr){
  lrng* lrng_ptr = (lrng*)R_ExternalPtrAddr(ptr);
  free(lrng_ptr);
  R_ClearExternalPtr(ptr);
};

SEXP make_lrng_C(){

  /* allocate the prng state */
  lrng* lrng_ptr = malloc(sizeof(struct lrng));
  lrng_ptr->A = 48271;
  lrng_ptr->M = 2147483647;
  lrng_ptr->Q = lrng_ptr->M / lrng_ptr->A;
  lrng_ptr->R = lrng_ptr->M % lrng_ptr->A;
  lrng_ptr->state = 1;
  lrng_ptr->t = 1;

  /* return to R with function to free the memory when ptr goes out of scope */
  SEXP ptr = PROTECT(R_MakeExternalPtr(lrng_ptr, R_NilValue, R_NilValue));
  R_RegisterCFinalizerEx(ptr,free_lrng_C,TRUE);
  UNPROTECT(1);
  return ptr;
};

SEXP random_lrng_C(SEXP ptr){
  lrng* lrng_ptr = (lrng*)R_ExternalPtrAddr(ptr);
  lrng_ptr->t = lrng_ptr->A * (lrng_ptr->state % lrng_ptr->Q) - lrng_ptr->R * (lrng_ptr->state / lrng_ptr->Q);
  if (lrng_ptr->t > 0){
    lrng_ptr->state = lrng_ptr->t;
  } else {
    lrng_ptr->state = lrng_ptr->t + lrng_ptr->M;
  }
  return Rf_ScalarReal(((double) lrng_ptr->state / lrng_ptr->M));
};
