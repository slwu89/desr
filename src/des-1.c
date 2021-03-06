/* --------------------------------------------------------------------------------
#
#   Discrete Event Simultion: A First Course
#   Algorithms from Ch. 1
#   Sean Wu (slwu89@berkeley.edu)
#   December 2019
#
-------------------------------------------------------------------------------- */

#include "des-1.h"


/* --------------------------------------------------------------------------------
#   algorithm 1.2.1: calculate delays under FIFO with finite capacity
-------------------------------------------------------------------------------- */

SEXP des_1_2_1_C(SEXP arrivals, SEXP services){
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


/* --------------------------------------------------------------------------------
#   program ssq1: a computational model of a single-server FIFO service node with infinite capacity
-------------------------------------------------------------------------------- */

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
  REAL(result)[2] = sum.d;
  REAL(result)[3] = sum.w;

  SEXP nms = PROTECT(Rf_allocVector(STRSXP, 4));
  Rf_namesgets(result, nms);
  SET_STRING_ELT(nms, 0, mkChar("r"));
  SET_STRING_ELT(nms, 1, mkChar("s"));
  SET_STRING_ELT(nms, 2, mkChar("d"));
  SET_STRING_ELT(nms, 3, mkChar("w"));

  UNPROTECT(4);
  return result;
};


/* --------------------------------------------------------------------------------
#   algorithm 1.3.1: compute discrete time evolution of inventory level for simple system (w/back ordering & no delivery lag)
-------------------------------------------------------------------------------- */

SEXP des_1_3_1_C(SEXP demands, SEXP sR, SEXP SR){

  int s = Rf_asInteger(sR);
  int S = Rf_asInteger(SR);

  int* d_ptr = INTEGER(demands);
  int d;

  int n = Rf_length(demands);

  /* we will return the inventory level and orders */
  int* l = (int*)calloc(n+1,sizeof(int));
  int* o = (int*)calloc(n,sizeof(int));

  l[0] = S;
  int i = 0;

  while(i < n){
    i++;
    if(l[i-1] < s){
      o[i-1] = S - l[i-1];
    } else {
      o[i-1] = 0;
    }
    d = d_ptr[i-1];
    l[i] = l[i-1] + o[i-1] - d;
  }

  /* terminal order to fill up inventory */
  i = n;
  o[i-1] = S - l[i];
  l[i] = S;

  SEXP lout = PROTECT(Rf_allocVector(INTSXP,n));
  SEXP oout = PROTECT(Rf_allocVector(INTSXP,n));

  int* lout_ptr = INTEGER(lout);
  int* oout_ptr = INTEGER(oout);

  memcpy(lout_ptr,&l[1],sizeof(int)*n);
  memcpy(oout_ptr,o,sizeof(int)*n);

  SEXP result = PROTECT(Rf_allocVector(VECSXP, 2));
  SET_VECTOR_ELT(result,0,lout);
  SET_VECTOR_ELT(result,1,oout);

  SEXP nms = PROTECT(Rf_allocVector(STRSXP, 2));
  Rf_namesgets(result, nms);
  SET_STRING_ELT(nms, 0, Rf_mkChar("l"));
  SET_STRING_ELT(nms, 1, Rf_mkChar("o"));

  UNPROTECT(4);
  free(l);
  free(o);

  return result;
};


/* --------------------------------------------------------------------------------
#   program sis1: simulates a simple (s,S) inventory system using demand as input argument
-------------------------------------------------------------------------------- */

SEXP des_sis1_C(SEXP demands, SEXP sR, SEXP SR){

  int s = Rf_asInteger(sR);
  int S = Rf_asInteger(SR);

  if(s >= S){
    Rf_error("please set s < S");
  }
  if(s < 0 || S < 0){
    Rf_error("inputs must be positive");
  }

  /* pointer to demand trace */
  int* d_ptr = INTEGER(demands);
  int n = Rf_length(demands);

  /* time interval index */
  int i = 0;
  /* current inventory level */
  int inv = S;
  /* amount of demand */
  int dem;
  /* amount of orders */
  int ord;

  /* output vector */
  SEXP output = PROTECT(Rf_allocVector(REALSXP, 5));
  SEXP nms = PROTECT(Rf_allocVector(STRSXP, 5));
  Rf_namesgets(output, nms);
  SET_STRING_ELT(nms, 0, Rf_mkChar("setup"));
  SET_STRING_ELT(nms, 1, Rf_mkChar("holding"));
  SET_STRING_ELT(nms, 2, Rf_mkChar("shortage"));
  SET_STRING_ELT(nms, 3, Rf_mkChar("order"));
  SET_STRING_ELT(nms, 4, Rf_mkChar("demand"));

  double* output_ptr = REAL(output);

  /* iterate over demands */
  while(i < n){
    i++;

    if(inv < s){
      ord = S - inv;
      output_ptr[0] += 1.; // setup
      output_ptr[3] += (double)ord; // order
    } else {
      ord = 0;
    }

    inv += ord; // no delivery lag
    dem = d_ptr[i-1];
    output_ptr[4] += (double)dem;

    if(inv > dem){
      output_ptr[1] += ((double)inv - 0.5 * (double)dem);
    } else {
      output_ptr[1] +=  pow((double)inv,2.) / (2.0 * dem);
      output_ptr[2] +=  pow((double)(dem - inv),2.) / (2.0 * dem);
    }
    inv -= dem;
  }

  /* final time step */
  if(inv < S){
    ord = S - inv; // match the final inventory
    output_ptr[0] += 1.;
    output_ptr[3] += (double)ord;
    inv += ord;
  }

  output_ptr[0] /= (double)n;
  output_ptr[1] /= (double)n;
  output_ptr[2] /= (double)n;
  output_ptr[3] /= (double)n;
  output_ptr[4] /= (double)n;

  UNPROTECT(2);
  return output;
};
