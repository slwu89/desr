# -------------------------------------------------------------------------------- #
#
#   Discrete Event Simultion: A First Course
#   Algorithms from Ch. 1
#   Sean Wu (slwu89@berkeley.edu)
#   December 2019
#
# -------------------------------------------------------------------------------- #

#' algorithm 1.2.1: calculate delays under FIFO with finite capacity
#'
#' If the arrival times a1, a2, . . . and service times s1, s2, . . . are known and if the server is initially idle, then this algorithm computes the delays d1,d2,... in a single-server FIFO service node with infinite capacity.
#' This algorithm computes the departure times c1, c2, . . . as a by-product of the computation.
#'
#' @param a vector of arrival times
#' @param s vector of service times
#'
#' @return d vector of delay times (how long each job waits in the queue prior to begin of service)
#'
#' @examples
#' a <- c(15,47,71,111,123,152,166,226,310,320)
#' s <- c(43,36,34,30,38,40,31,29,36,30)
#' des1_2_1(a,s)
#' @useDynLib desr des1_2_1_C
#' @export
des1_2_1 <- function(a,s){
  .Call(des1_2_1_C,as.numeric(a),as.numeric(s))
}

#' program ssq1: a computational model of a single-server FIFO service node with infinite capacity
#'
#' This program simulates a single-server FIFO service node using arrival
#' times and service times read from a \code{data.frame}.  The server is assumed
#' to be idle when the first job arrives.  All jobs are processed completely
#' so that the server is again idle at the end of the simulation.   The
#' output statistics are the average interarrival time, average service
#' time, the average delay in the queue, and the average wait in the service
#' node.
#'
#' @param df a \code{data.frame} with 2 columns: arrival and service times (in that order)
#'
#' @return a named vector with job-averaged interarrival time (r), service time (s), delay (d), and wait (w)
#' @examples
#' data(ssq1dat)
#' des_ssq1(ssq1dat)
#' @useDynLib desr des_ssq1_C
#' @export
des_ssq1 <- function(df){
  .Call(des_ssq1_C,df)
}
