#ifndef HAMIL_H
#define HAMIL_H

#include <armadillo>

#include "params.h"
#include "traj.h"
#include <cmath>

struct hamil {

  // specific to flat adiabat hamil
  const int qdim = 2;
  const int cdim = 2;

  arma::cx_mat Ve;
  arma::cx_mat Ue;
  arma::cx_cube Fe;
  arma::vec F;
  arma::vec eigs;
  arma::cx_cube dij;

  void HamilD(traj &curr_traj);
  void HamilA(traj &curr_traj);
  void set_params(const params &);

  double jA, jlx, jbx; // Defines Hamil in Joe's code
};

#endif // HAMIL_H
