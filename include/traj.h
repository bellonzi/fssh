#ifndef TRAJ_H
#define TRAJ_H

#include <armadillo>

class traj {

  void initial();
  void propagate();

  arma::vec x;
  arma::vec p;
  arma::cx_vec psi;
  int surface;
};

#endif // TRAJ_H
