% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/des-2.R
\name{des_2_2_2}
\alias{des_2_2_2}
\title{algorithm 2.2.2: Given the prime modulus m and any associated full-period, modulus- compatible multiplier a the following algorithm generates all the full-period, modulus- compatible multipliers relative to m.}
\usage{
des_2_2_2(a, m)
}
\arguments{
\item{a}{full-period, modulus-compatible multiplier}

\item{m}{modulus, a fixed large prime integer}
}
\value{
a vector of all other full-period modulous-compatible multipliers
}
\description{
Given the prime modulus m and any full-period multiplier a, the following algorithm generates all the full-period multipliers relative to m.
}
\examples{
des_2_2_2(3,401) # should give (3, 6, 12, 13, 15, 17, 19, 21, 23, 66)
}
