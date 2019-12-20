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

#include <stdlib.h>
#include <string.h>

#include <R.h>
#include <Rinternals.h>
#include <Rmath.h>


/* --------------------------------------------------------------------------------
#   functions
-------------------------------------------------------------------------------- */

/* algorithm 1.2.1: calculate delays under FIFO with finite capacity */
SEXP des1_2_1_C(SEXP arrivals, SEXP services);

/* program ssq1: a computational model of a single-server FIFO service node with infinite capacity */
SEXP des_ssq1_C(SEXP df);

#endif
