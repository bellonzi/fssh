#ifndef TRAJ_H
#define TRAJ_H

#include "params.h"
#include <armadillo>

struct traj {
  void initial(const params &);

  arma::vec x;
  arma::vec p;
  arma::vec F;
  arma::cx_vec psi;
  int surface;
};

#endif // TRAJ_H
