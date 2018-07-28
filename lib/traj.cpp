#include "traj.h"

void traj::initial() {

  std::cout << "Sigma_p is set to zero\n\n" << std::endl;
  sigp.zeros(cdim);

  x.zeros(cdim);
  p.zeros(cdim);
  psi.zeros(qdim);

  arma::vec randvec;
  randvec.zeros(cdim + cdim % 2);

  // initial x sampled from gaussian
  boxmuller(randvec);
  x = sigx % randvec.head(cdim) + x0;
  // initial p sampled from gaussian
  boxmuller(randvec);
  p = sigp % randvec.head(cdim) + p0;

  // initial psi in adiabatic basis
  psi(0) = arma::cx_double(1 / sqrt(2), 0);
  psi(1) =
      sqrt(1.0 - (psi(0) * psi(0))) * arma::cx_double(cos(phase), sin(phase));
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

/* * * * * * * * * * * * * * * * * * * * * * * */
void traj::propagate() {
  // x + p/m*dt/2
  x = x + p * dt2;

  // update Hamil to get Fsurf
  sys::HamilA();
  // p + F*dt
  p = p + (sys::Fsurf)*dt;

  // x + p/m*dt/2
  x = x + p * dt2;

  return;
}
