#include "traj.h"

void traj::initial(const params &config) {

  // FIXME sigp is already 0 so I commented this out. We're passing params as
  // const reference everywhere, so sigp can never be altered. Is this okay?
  // std::cout << "Sigma_p is set to zero\n\n" << std::endl;
  // config.sigp.zeros(config.cdim);

  x.zeros(config.cdim);
  p.zeros(config.cdim);
  psi.zeros(config.qdim);

  arma::vec randvec;
  randvec.zeros(config.cdim + config.cdim % 2);

  // initial x sampled from gaussian
  config.boxmuller(randvec);
  x = config.sigx % randvec.head(config.cdim) + config.x0;
  // initial p sampled from gaussian
  config.boxmuller(randvec);
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

  std::cout << "run" << std::endl;
  return;
}
