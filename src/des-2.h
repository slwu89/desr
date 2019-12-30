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

#endif
