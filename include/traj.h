#ifndef TRAJ_H
#define TRAJ_H

#include "params.h"
#include <armadillo>
#include <random>

struct traj {
  void initial(const params &, std::mt19937 &prng);

  arma::vec x;
  arma::vec p;
  arma::cx_vec psi;
  int surface;
};

#endif // TRAJ_H
