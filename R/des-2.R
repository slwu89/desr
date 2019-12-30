# -------------------------------------------------------------------------------- #
#
#   Discrete Event Simultion: A First Course
#   Algorithms from Ch. 2
#   Sean Wu (slwu89@berkeley.edu)
#   December 2019
#
# -------------------------------------------------------------------------------- #

#' algorithm 2.1.1: determine if \code{a} is full period multiplier relative to prime modulus \code{m}
#'
#' This algorithm, based upon Theorem 2.1.2, can be used to determine
#' if a is a full-period multiplier relative to the prime modulus m.
#' If m is not prime Algorithm 2.1.1 may not halt, although the while loop
#' will occasionally check for user interrupts.
#'
#' @param a multiplier, a fixed integer
#' @param m modulus, a fixed large prime integer
#'
#' @return \code{true} or \code{false} if \code{a} is a full period multiplier
#'
#' @examples
#' des_2_1_1(7,13) # true
#' des_2_1_1(5,13) # false
#' @useDynLib desr des_2_1_1_C
#' @export
des_2_1_1 <- function(a,m){
  .Call(des_2_1_1_C,as.integer(a),as.integer(m))
}

#' algorithm 2.1.2: given mod \code{m} and a full-period multiplier \code{a}, determine all other full-period multipliers
#'
#' Given the prime modulus m and any full-period multiplier a, the following algorithm generates all the full-period multipliers relative to m.
#'
#' @param a multiplier, a fixed integer
#' @param m modulus, a fixed large prime integer
#'
#' @return a vector of integers
#'
#' @examples
#' des_2_1_2(2,13) # should give 2,6,7,11
#' @useDynLib desr des_2_1_2_C
#' @export
des_2_1_2 <- function(a,m){
  .Call(des_2_1_2_C,as.integer(a),as.integer(m))
}
