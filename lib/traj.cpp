#include "traj.h"

void traj::initial_zero(const params &config) {

  x.zeros(config.cdim);
  p.zeros(config.cdim);
  psi.zeros(config.qdim);
  surface = 0;

  return;
}

void traj::initial(const params &config, std::mt19937 &prng) {

  x.zeros(config.cdim);
  p.zeros(config.cdim);
  psi.zeros(config.qdim);

  arma::vec randvec(config.cdim + config.cdim % 2);

  // initial x sampled from gaussian
  // The random seed is set in main.cpp
  std::normal_distribution<> rand_gaussian{0, 1};
  for (int i = 0; i < config.cdim; ++i) {
    randvec(i) = rand_gaussian(prng);
  }
  x = config.sigx % randvec.head(config.cdim) + config.x0;
  // initial p sampled from gaussian
  for (int i = 0; i < config.cdim; ++i) {
    randvec(i) = rand_gaussian(prng);
  }
  p = config.sigp % randvec.head(config.cdim) + config.p0;

  // initial psi in adiabatic basis
  psi(0) = arma::cx_double(1 / sqrt(2), 0);
  psi(1) = sqrt(1.0 - (psi(0) * psi(0))) *
           arma::cx_double(cos(config.phase), sin(config.phase));
  // std::cout << "psi:\n" << psi << std::endl;
  // std::cout << "x:\n" << x << std::endl;
  // std::cout << "p:\n" << p << std::endl;
  std::uniform_real_distribution<double> rand_01(0.0, 1.0);
  if (rand_01(prng) < (psi(0) * conj(psi(0))).real())
    surface = 0;
  else
    surface = 1;

  arma::cx_double normie = checknorm();
  std::cout << normie << std::endl;

  return;
}

arma::cx_double traj::checknorm(){

  arma::cx_double norm = arma::cdot(psi,psi);
  return norm;
}

rk4::rk4(const params &config) {

  x.zeros(config.cdim);
  p.zeros(config.cdim);
  psi.zeros(config.qdim);

}

traj add_rk4(traj &curr_traj, rk4 &curr_rk4){

  traj temp_traj = curr_traj;

  temp_traj.x += curr_rk4.x;
  temp_traj.p += curr_rk4.p;
  temp_traj.psi += curr_rk4.psi;

  return temp_traj;
}

