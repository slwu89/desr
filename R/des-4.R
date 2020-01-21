# -------------------------------------------------------------------------------- #
#
#   Discrete Event Simultion: A First Course
#   Algorithms from Ch. 4
#   Sean Wu (slwu89@berkeley.edu)
#   January 2020
#
# -------------------------------------------------------------------------------- #

#' algorithm 4.1.1: Welford's one pass algorithm
#'
#' Calculate the sample mean and standard deviation in one pass via
#' Welford's algorithm.
#'
#' @param sample a vector of values (will be coerced by \code{\link{as.numeric}})
#'
#' @return a vector with sample mean and standard deviation
#'
#' @examples
#' samp <- rnorm(n=1e4)
#' mean(samp);sd(samp)
#' des_4_1_1(samp)
#' @useDynLib desr des_4_1_1_C
#' @export
des_4_1_1 <- function(sample){
  .Call(des_4_1_1_C,as.numeric(sample))
}

#' algorithm 4.2.1: discrete data histrogram
#'
#' Given integers a, b with a < b and integer-valued data x1, x2, . . . the following algorithm computes a discrete-data histogram.
#'
#' @param a lower bound
#' @param b upper bound
#' @param data a vector of values (will be coerced by \code{\link{as.integer}})
#'
#' @return a list with \code{count}, \code{outliers_lo}, and \code{outliers_hi}
#'
#' @examples
#' samp <- rpois(n=30,lambda=10)
#' des_4_2_1(a=2,b=35,data=samp)
#' @useDynLib desr des_4_2_1_C
#' @export
des_4_2_1 <- function(a,b,data){
  .Call(des_4_2_1_C,as.integer(a),as.integer(b),as.integer(data))
}
