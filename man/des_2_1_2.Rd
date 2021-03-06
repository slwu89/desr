% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/des-2.R
\name{des_2_1_2}
\alias{des_2_1_2}
\title{algorithm 2.1.2: given mod \code{m} and a full-period multiplier \code{a}, determine all other full-period multipliers}
\usage{
des_2_1_2(a, m)
}
\arguments{
\item{a}{multiplier, a fixed integer}

\item{m}{modulus, a fixed large prime integer}
}
\value{
a vector of integers
}
\description{
Given the prime modulus m and any full-period multiplier a, the following algorithm generates all the full-period multipliers relative to m.
}
\examples{
des_2_1_2(2,13) # should give 2,6,7,11
}
