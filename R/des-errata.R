# -------------------------------------------------------------------------------- #
#
#   Discrete Event Simultion: A First Course
#   Appendices, extras, and helper functions
#   Sean Wu (slwu89@berkeley.edu)
#   December 2019
#
# -------------------------------------------------------------------------------- #

#' Greatest Common Divisor (GCD)
#'
#' Euclidean Algorithm to compute GCD.
#'
#' @param a a positive integer
#' @param b a positive integer
#'
#' @return the GCD
#'
#' @examples
#' des_gcd(10,21) # returns 1
#' des_gcd(12,24) # returns 12
#' @useDynLib desr gcd_C
#' @export
des_gcd <- function(a,b){
  .Call(gcd_C,as.integer(a),as.integer(b))
}


#' Sieve of Eratosthenes
#'
#' Finds all prime numbers between 2 and N (N>2)
#'
#' @param N a positive integer greater than 2
#'
#' @return a vector of prime numbers
#'
#' @examples
#' # returns 25 prime numbers
#' des_sieve(100)
#' @useDynLib desr sieve_C
#' @export
des_sieve <- function(N){
  .Call(sieve_C,as.integer(N))
}

#' Approximate factorization
#'
#' If m is prime and a > 1 then no factorization of the form m = aq is possible,
#' but an approximate factorization of the form m = aq+r is possible. q = floor(m/a) and r = m mod a.
#'
#' @param a an integer
#' @param m an integer
#'
#' @return a vector of \code{q} and \code{r}
#'
#' @examples
#' m <- as.integer((2^31)-1)
#' a <- 48271
#' approx_factor(a,m)
#' @useDynLib desr approx_factor_C
#' @export
approx_factor <- function(a,m){
  .Call(approx_factor_C,as.integer(a),as.integer(m))
}
