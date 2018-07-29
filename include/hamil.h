#ifndef HAMIL_H
#define HAMIL_H

#include <armadillo>

#include "params.h"
#include "traj.h"
#include <cmath>

struct hamil {

  arma::cx_mat Ve;
  arma::cx_mat Ue;
  arma::cx_cube Fe;
  arma::vec Fsurf;
  arma::vec eigs;

  void HamilD(const params &, traj &curr_traj);

  void HamilA(const params &, traj &curr_traj);
  void set_params(const params &);

  double jA, jlx, jbx; // Defines Hamil in Joe's code
};

#endif // HAMIL_H
