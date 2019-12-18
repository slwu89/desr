/* --------------------------------------------------------------------------------
#
#   Discrete Event Simultion: A First Course
#   Algorithms from Ch. 1
#   Sean Wu (slwu89@berkeley.edu)
#   December 2019
#
-------------------------------------------------------------------------------- */

#ifndef DES_1_H
#define DES_1_H

#include <R.h>
#include <Rinternals.h>
#include <Rmath.h>


/* --------------------------------------------------------------------------------
#   functions
-------------------------------------------------------------------------------- */

/* algorithm 1.2.1: calculate delays under FIFO with finite capacity */
SEXP des1_2_1(SEXP arrivals, SEXP services);

#endif
