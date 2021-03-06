% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/des-errata.R
\name{approx_factor}
\alias{approx_factor}
\title{Approximate factorization}
\usage{
approx_factor(a, m)
}
\arguments{
\item{a}{an integer}

\item{m}{an integer}
}
\value{
a vector of \code{q} and \code{r}
}
\description{
If m is prime and a > 1 then no factorization of the form m = aq is possible,
but an approximate factorization of the form m = aq+r is possible. q = floor(m/a) and r = m mod a.
}
\examples{
m <- as.integer((2^31)-1)
a <- 48271
approx_factor(a,m)
}
