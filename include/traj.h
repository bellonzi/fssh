#ifndef TRAJ_H
#define TRAJ_H

#include "lib.h"
#include <armadillo>

struct traj {

  void initial();

  arma::vec x;
  arma::vec p;
  arma::vec F;
  arma::cx_vec psi;
  int surface;
};

#endif // TRAJ_H
