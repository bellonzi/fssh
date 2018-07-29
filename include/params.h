#ifndef NIB_LIB
#define NIB_LIB

#include <armadillo>
#include <cmath>

const double two_pi = 2.0 * M_PI;

struct params {
  void read_input(void);                    // read run.in
  void boxmuller(arma::vec &randvec) const; // make random normal noise

  // global variables that are set in lib.C
  int ntrajs;
  int nsteps;
  double dt, dt2;

  int qdim;
  int cdim;
  double jA, jlx, jbx; // Defines Hamil in Joe's code

  double phase;
  arma::vec sigx;
  arma::vec sigp;
  arma::vec x0;
  arma::vec p0;
};

#endif // NIB_LIB
