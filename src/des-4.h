/* --------------------------------------------------------------------------------
#
#   Discrete Event Simultion: A First Course
#   Algorithms from Ch. 4
#   Sean Wu (slwu89@berkeley.edu)
#   January 2020
#
-------------------------------------------------------------------------------- */

#ifndef DES_4_H
#define DES_4_H

#include <stdlib.h>
#include <string.h>

#include <R.h>
#include <Rinternals.h>
#include <Rmath.h>

#include <R_ext/Utils.h> // for user interrupt checking


/* --------------------------------------------------------------------------------
#   functions
-------------------------------------------------------------------------------- */

/* algorithm 4.1.1: Welford's one pass algorithm */
SEXP des_4_1_1_C(SEXP sampleR);



#endif
