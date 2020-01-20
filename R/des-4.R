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
