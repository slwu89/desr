/* --------------------------------------------------------------------------------
#
#   Discrete Event Simultion: A First Course
#   Algorithms from Ch. 1
#   Sean Wu (slwu89@berkeley.edu)
#   December 2019
#
-------------------------------------------------------------------------------- */

#include "des-1.h"

/* algorithm 1.2.1: calculate delays under FIFO with finite capacity */
SEXP des1_2_1_C(SEXP arrivals, SEXP services){
  int n = LENGTH(arrivals);
  if(LENGTH(services) != n){
    error("'arrivals' and 'services' vectors must be the same length\n");
  }

  /* vector of service completions (departures) */
  double* c = (double*)calloc(n+1,sizeof(double));
  c[0] = 0.;

  /* vector of arrivals (a) and services times (s) */
  double* a = (double*)calloc(n+1,sizeof(double));
  double* s = (double*)calloc(n+1,sizeof(double));

  memcpy(a+1,REAL(arrivals),sizeof(double)*n);
  memcpy(s+1,REAL(services),sizeof(double)*n);

  /* departure times (the output) */
  SEXP d = PROTECT(allocVector(REALSXP,n));
  double* d_i = REAL(d); /* d_i is the departure time of job i */

  int i = 0;

  while(i < n){

    i++;
    double a_i = a[i];

    if(a_i < c[i-1]){
      /* calculate delay for job i */
      d_i[i-1] = c[i-1] - a_i;
    } else {
      /* job i has no delay */
      d_i[i-1] = 0.;
    }

    /* calculate departure time for job i */
    c[i] = a_i + d_i[i-1] + s[i];
  }

  /* free memory/unprotect and return */
  free(c);
  free(a);
  free(s);
  UNPROTECT(1);

  return d;
};


/* program ssq1: a computational model of a single-server FIFO service node with infinite capacity */
SEXP des_ssq1_C(SEXP df){

  /* sanity checks */
  if(!Rf_isFrame(df) || Rf_length(df) != 2){
    error("'df' must be a data.frame object with 2 columns for arrivals and service times\n");
  }

  SEXP arrival_in = PROTECT(VECTOR_ELT(df, 0));
  SEXP service_in = PROTECT(VECTOR_ELT(df, 1));

  double* a_ptr = REAL(arrival_in);
  double* s_ptr = REAL(service_in);

  if(!Rf_isReal(arrival_in) || !Rf_isReal(service_in)){
    error("arrivals and service times must be numeric (float) values\n");
  }

  /* number of jobs */
  int n = Rf_length(arrival_in);

  /* variables for job i */
  double a_i = 0.; /* arrival time */
  double d_i = 0.; /* delay in queue */
  double s_i = 0.; /* service time */
  double w_i = 0.; /* wait (delay + service) */
  double c_i = 0.; /* departure time */

  /* time-averaged statistics */
  struct {                         /* sum of ...           */
    double d;                      /*   delay times        */
    double w;                      /*   wait times         */
    double s;                      /*   service times      */
    double r;                      /*   interarrival times */
  } sum = {0.0, 0.0, 0.0, 0.0};

  /* trace-driven simulation */
  for(int i=0; i<n; i++){

    a_i = a_ptr[i];

    if(a_i < c_i){
      /* delay in queue */
      d_i = c_i - a_i;
    } else {
      /* no delay */
      d_i = 0.;
    }

    s_i = s_ptr[i];
    w_i = d_i + s_i;
    c_i = a_i + w_i; /* time of departure */

    sum.d += d_i;
    sum.w += w_i;
    sum.s += s_i;
  }

  sum.d /= (double)n;
  sum.w /= (double)n;
  sum.s /= (double)n;
  sum.r = a_i / (double)n;

  SEXP result = PROTECT(Rf_allocVector(REALSXP, 4));
  REAL(result)[0] = sum.r;
  REAL(result)[1] = sum.s;
  REAL(result)[3] = sum.d;
  REAL(result)[4] = sum.w;

  SEXP nms = PROTECT(Rf_allocVector(STRSXP, 4));
  Rf_namesgets(result, nms);
  SET_STRING_ELT(nms, 0, mkChar("r"));
  SET_STRING_ELT(nms, 1, mkChar("s"));
  SET_STRING_ELT(nms, 2, mkChar("d"));
  SET_STRING_ELT(nms, 3, mkChar("w"));

  UNPROTECT(4);
  return result;
};
