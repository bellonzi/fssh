#ifndef HAMIL_H
#define HAMIL_H

#include <armadillo>

#include "lib.h"
#include "traj.h"
#include <cmath>

struct hamil {

  arma::cx_mat Ve;
  arma::cx_mat Ue;
  arma::cx_cube Fe;
  arma::vec Fsurf;
  arma::vec eigs;

  void HamilD(traj &curr_traj);

  void HamilA(traj &curr_traj);
};

#endif // HAMIL_H
