/* --------------------------------------------------------------------------------
#
#   Discrete Event Simultion: A First Course
#   Algorithms from Ch. 2
#   Sean Wu (slwu89@berkeley.edu)
#   December 2019
#
-------------------------------------------------------------------------------- */

#ifndef DES_2_H
#define DES_2_H

#include <stdlib.h>
#include <string.h>

#include <R.h>
#include <Rinternals.h>
#include <Rmath.h>

#include <R_ext/Utils.h> // for user interrupt checking

#include "des-errata.h" // for gcd


/* --------------------------------------------------------------------------------
#   functions
-------------------------------------------------------------------------------- */

/* algorithm 2.1.1: determine if multiplier relative to the prime modulus m */
SEXP des_2_1_1_C(SEXP aR, SEXP mR);

/* algorithm 2.1.2: given mod m and a full-period multiplier a, determine all other full-period multipliers */
SEXP des_2_1_2_C(SEXP aR, SEXP mR);

/* algorithm 2.2.1: evaluate ax mod m without producing any integers larger than m-1 */
SEXP des_2_2_1_C(SEXP xR, SEXP aR, SEXP mR);

/* internal C version of 2.2.1 */
int g(const int x, const int a, const int m);

/* algorithm 2.2.2: Given the prime modulus m and any associated full-period, modulus- compatible multiplier a the following algorithm generates all the full-period, modulus- compatible multipliers relative to m. */
SEXP des_2_2_2_C(SEXP aR, SEXP mR);

/* algorithm 2.5.1 Given the state transition function g(·) and initial state x0, this algorithm determines the fundamental pair (s, p)  */
SEXP des_2_5_1_C(SEXP g, SEXP x0, SEXP rho);

/* --------------------------------------------------------------------------------
#   Lehman random number generator via external ptr
-------------------------------------------------------------------------------- */

/* store the state of the RNG */
typedef struct lrng {
  long A;     // multiplier
  long M;     // modulus
  long Q;     // quotient
  long R;     // remainder
  long state;
  long t;
} lrng;

void free_lrng_C(SEXP ptr);

SEXP make_lrng_C();

SEXP random_lrng_C(SEXP ptr);

#endif
