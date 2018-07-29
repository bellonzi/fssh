#include "traj.h"

void traj::initial(const params &config) {

  // FIXME Nicole, I noticed that sigp is already 0, so I commented out the
  // lines below where sigp is set to zero again. Because we're passing params
  // as const reference everywhere, sigp can never be altered. Does this seem
  // sufficient to you?

  // std::cout << "Sigma_p is set to zero\n\n" << std::endl;
  // config.sigp.zeros(config.cdim);

  x.zeros(config.cdim);
  p.zeros(config.cdim);
  F.zeros(config.cdim);
  psi.zeros(config.qdim);

  arma::vec randvec(config.cdim + config.cdim % 2);

  // initial x sampled from gaussian
  // The random seed is set in fssh.cpp
  randvec.randn();
  x = config.sigx % randvec.head(config.cdim) + config.x0;
  // initial p sampled from gaussian
  randvec.randn();
  p = config.sigp % randvec.head(config.cdim) + config.p0;

  // initial psi in adiabatic basis
  psi(0) = arma::cx_double(1 / sqrt(2), 0);
  psi(1) = sqrt(1.0 - (psi(0) * psi(0))) *
           arma::cx_double(cos(config.phase), sin(config.phase));
  // std::cout << "psi:\n" << psi << std::endl;
  // std::cout << "x:\n" << x << std::endl;
  // std::cout << "p:\n" << p << std::endl;
  double whichsurf = rand() * (1.0 / RAND_MAX);
  if (whichsurf < (psi(0) * conj(psi(0))).real())
    surface = 0;
  else
    surface = 1;

  // std::cout << "run" << std::endl;
  return;
}
