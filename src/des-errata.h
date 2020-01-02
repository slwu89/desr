/* --------------------------------------------------------------------------------
#
#   Discrete Event Simultion: A First Course
#   Appendices, extras, and helper functions
#   Sean Wu (slwu89@berkeley.edu)
#   December 2019
#
-------------------------------------------------------------------------------- */

#ifndef DES_ERRATA
#define DES_ERRATA

#include <stdlib.h>
#include <string.h>

#include <R.h>
#include <Rinternals.h>
#include <Rmath.h>


/* --------------------------------------------------------------------------------
#   functions
-------------------------------------------------------------------------------- */

SEXP gcd_C(SEXP aR, SEXP bR);

int gcd(int a, int b);

SEXP sieve_C(SEXP NR);

SEXP approx_factor_C(SEXP aR, SEXP MR);

int* approx_factor(const int a, const int M);

#endif
