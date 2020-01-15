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

#' algorithm 2.2.1: evaluate ax mod m without producing any integers larger than m-1
#'
#' If m = aq+r is prime, r < q, and x ∈ Xm, then g(x) = ax mod m can be evaluated as follows without producing any intermediate or final values larger than m − 1 in magnitude.
#'
#' @param x value in \{1,2,...,m-1\}
#' @param a multiplier, a fixed integer
#' @param m modulus, a fixed large prime integer
#'
#' @return value of function
#'
#' @examples
#'  # gives same result
#'  des_2_2_1(x = 9,a = 3,m = 401)
#'  (3*9) %% 401
#'  # to avoid overflow
#' m <- as.integer((2^31)-1)
#' a <- 48271
#' x <- 53423L
#' (a*x) %% m
#' des_2_2_1(x,a,m)
#' @useDynLib desr des_2_2_1_C
#' @export
des_2_2_1 <- function(x,a,m){
  .Call(des_2_2_1_C,as.integer(x),as.integer(a),as.integer(m))
}

#' algorithm 2.2.2: Given the prime modulus m and any associated full-period, modulus- compatible multiplier a the following algorithm generates all the full-period, modulus- compatible multipliers relative to m.
#'
#' Given the prime modulus m and any full-period multiplier a, the following algorithm generates all the full-period multipliers relative to m.
#'
#' @param a full-period, modulus-compatible multiplier
#' @param m modulus, a fixed large prime integer
#'
#' @return a vector of all other full-period modulous-compatible multipliers
#'
#' @examples
#' des_2_2_2(3,401) # should give (3, 6, 12, 13, 15, 17, 19, 21, 23, 66)
#' @useDynLib desr des_2_2_2_C
#' @export
des_2_2_2 <- function(a,m){
  .Call(des_2_2_2_C,as.integer(a),as.integer(m))
}

#' algorithm 2.5.1 Given the state transition function g(·) and initial state x0, this algorithm determines the fundamental pair (s, p)
#'
#' This algorithm trades memory requirements for fast speed; all intermediate
#' values are stored in a linked list to minimize calls to \code{g}.
#'
#' @param g function
#' @param x0 initial state
#'
#' @return fundamental pair (starting point, period)
#'
#' @examples
#' midsq <- function(x){as.integer(floor((x^2)/100) %% 10000)}
#' x0 <- 1726 # this x0 will give (s,p) = (6,4)
#' x0 <- 6283 # this x0 will give (s,p) = (7,1)
#' x0 <- 5600 # this x0 will give (s,p) = (0,4)
#' des_2_5_1(midsq,x0)
#' @useDynLib desr des_2_5_1_C
#' @export
des_2_5_1 <- function(g,x0){
  .Call(des_2_5_1_C,g,as.integer(x0),new.env())
}

#' algorithm 2.5.2 Given the state transition function g(·) and initial state x0, this algorithm determines the fundamental pair (s, p)
#'
#' This algorithm trades slow speed for low memory; all intermediate
#' values are generated on the fly via calls to \code{g}.
#'
#' @param g function
#' @param x0 initial state
#'
#' @return fundamental pair (starting point, period)
#'
#' @examples
#' midsq6 <- function(x){as.integer(floor((x^2)/1000) %% 1000000)}
#' x0 <- 141138 # this x0 will give (s,p) = (296, 29)
#' x0 <- 119448 # this x0 will give (s,p) = (428, 210)
#' x0 <- 586593 # this x0 will give (s,p) = (48, 13)
#' x0 <- 735812 # this x0 will give (s,p) = (225, 1)
#' x0 <- 613282 # this x0 will give (s,p) = (469, 20)
#' des_2_5_2(midsq6,x0)
#' @useDynLib desr des_2_5_2_C
#' @export
des_2_5_2 <- function(g,x0){
  .Call(des_2_5_2_C,g,as.integer(x0),new.env())
}

#' algorithm 2.5.3 Given the state transition function g(·) and initial state x0, this algorithm determines the fundamental pair (s, p)
#'
#' This algorithm takes the best features of \code{\link[desr]{des_2_5_1}} and \code{\link[desr]{des_2_5_2}}.
#'
#' @param g function
#' @param x0 initial state
#'
#' @return fundamental pair (starting point, period)
#'
#' @examples
#' midsq6 <- function(x){as.integer(floor((x^2)/1000) %% 1000000)}
#' x0 <- 141138 # this x0 will give (s,p) = (296, 29)
#' x0 <- 119448 # this x0 will give (s,p) = (428, 210)
#' x0 <- 586593 # this x0 will give (s,p) = (48, 13)
#' x0 <- 735812 # this x0 will give (s,p) = (225, 1)
#' x0 <- 613282 # this x0 will give (s,p) = (469, 20)
#' des_2_5_3(midsq6,x0)
#' @useDynLib desr des_2_5_3_C
#' @export
des_2_5_3 <- function(g,x0){
  .Call(des_2_5_3_C,g,as.integer(x0),new.env())
}


# --------------------------------------------------------------------------------
#   Lehman random number generator via external ptr
# --------------------------------------------------------------------------------

#' make the prng
#'
#' @useDynLib desr make_lrng_C
#' @export
make_lrng <- function(){
  .Call(make_lrng_C)
}

#' sample the prng
#'
#' @useDynLib desr random_lrng_C
#' @export
random_lrng <- function(ptr){
  .Call(random_lrng_C,ptr)
}
