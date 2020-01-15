/* --------------------------------------------------------------------------------
#
#   Discrete Event Simultion: A First Course
#   Random number generation routines
#   Sean Wu (slwu89@berkeley.edu)
#   January 2020
#
-------------------------------------------------------------------------------- */

#include "rng.h"

/* initial seed, use 0 < DEFAULT < MODULUS   */
static long seed = 123456789L; // seed is the state of the generator


/* --------------------------------------------------------------------------------
#   use a Lehmer random number generator to produce a uniform(0,1) variate
-------------------------------------------------------------------------------- */

double Random(void){
  const long A = 48271;
  const long M = 2147483647;
  const long Q = M / A;
  const long R = M % A;

  long t = A * (seed % Q) - R * (seed / Q);
  if(t > 0){
    seed = t;
  } else {
    seed = t + M;
  }

  return (double) seed / M;
};


/* --------------------------------------------------------------------------------
#   produce a Unif(a,b) random variate
-------------------------------------------------------------------------------- */

double Uniform(const double a, const double b){
  return a + (b - a) * Random();
};


/* --------------------------------------------------------------------------------
#   produce a integer (inclusive) Unif(a,b) random variate
-------------------------------------------------------------------------------- */

long Equilikely(const long a, const long b){
  return a + (long)((b - a) * Random());
};


/* --------------------------------------------------------------------------------
#   produce an exponential random variate with rate 1/mu
-------------------------------------------------------------------------------- */

double Exponential(const double mu){
  return (-mu * log(1. - Random()));
};
