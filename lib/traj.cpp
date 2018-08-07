#include "traj.h"

void traj::initial(const params &config, std::mt19937 &prng) {

  // FIXME Nicole, I noticed that sigp is already 0, so I commented out the
  // lines below where sigp is set to zero again. Because we're passing params
  // as const reference everywhere, sigp can never be altered. Does this seem
  // sufficient to you?

  // std::cout << "Sigma_p is set to zero\n\n" << std::endl;
  // config.sigp.zeros(config.cdim);

  x.zeros(config.cdim);
  p.zeros(config.cdim);
  psi.zeros(config.qdim);

  arma::vec randvec(config.cdim + config.cdim % 2);

  // initial x sampled from gaussian
  // The random seed is set in fssh.cpp
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

  // std::cout << "run" << std::endl;
  return;
}

rk4::rk4(const params &config) {

  x.zeros(config.cdim);
  p.zeros(config.cdim);
  psi.zeros(config.qdim);

}


