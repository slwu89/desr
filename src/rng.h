/* --------------------------------------------------------------------------------
#
#   Discrete Event Simultion: A First Course
#   Random number generation routines
#   Sean Wu (slwu89@berkeley.edu)
#   January 2020
#
-------------------------------------------------------------------------------- */

#ifndef RNG_H
#define RNG_H

#include <math.h>

double Random(void);

double Uniform(const double a, const double b);

long   Equilikely(const long a, const long b);

double Exponential(const double mu);

#endif
