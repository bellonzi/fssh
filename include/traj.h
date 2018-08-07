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

struct rk4 {
  arma::vec x;
  arma::vec p;
  arma::cx_vec psi;

  public:
    rk4 (const params &);
};

traj add_rk4(traj &, rk4 &);

#endif // TRAJ_H
