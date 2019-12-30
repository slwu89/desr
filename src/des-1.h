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
SEXP des_1_2_1_C(SEXP arrivals, SEXP services);

/* program ssq1: a computational model of a single-server FIFO service node with infinite capacity */
SEXP des_ssq1_C(SEXP df);

/* algorithm 1.3.1: compute discrete time evolution of inventory level for simple system (w/back ordering & no delivery lag) */
SEXP des_1_3_1_C(SEXP demands, SEXP sR, SEXP SR);

/* program sis1: simulates a simple (s,S) inventory system using demand as input argument */
SEXP des_sis1_C(SEXP demands, SEXP sR, SEXP SR);

#endif
