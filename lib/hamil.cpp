#include "hamil.h"

/* * * * * * * * * * * * * * * * * * * * * * * */
void hamil::HamilD(const params &config, traj &curr_traj) {

  // Hamiltonian with flat adiabats
  double theta = two_pi * (jlx * std::erf(jbx * curr_traj.x(0)) + 1.0) / 4.0;
  double dthetadx0 =
      two_pi * jlx * jbx * std::exp(std::pow(jbx * curr_traj.x(0), 2)) / 4.0;
  double phi = 0.3 * jlx * curr_traj.x(1);
  double dphidx1 = 0.3 * jlx;

  Ve.zeros(config.qdim, config.qdim);
  Ve(0, 0) = jA * std::cos(theta);
  Ve(1, 1) = -jA * std::cos(theta);
  Ve(0, 1) = jA * std::sin(theta) * std::exp(arma::cx_double(0, phi));
  Ve(1, 0) = conj(Ve(0, 1));

  Fe.zeros(config.qdim, config.qdim, config.cdim);
  Fe(0, 0, 0) = -jA * std::sin(theta) * dthetadx0;
  Fe(1, 1, 0) = jA * std::sin(theta) * dthetadx0;
  Fe(0, 1, 0) =
      jA * std::cos(theta) * std::exp(arma::cx_double(0, phi)) * dthetadx0;
  Fe(1, 0, 0) = conj(Fe(0, 1, 0));

  Fe(0, 1, 1) = jA * std::sin(theta) * std::exp(arma::cx_double(0, phi)) *
                arma::cx_double(0, dphidx1);
  Fe(1, 0, 1) = conj(Fe(0, 1, 1));

  return;
}

/* * * * * * * * * * * * * * * * * * * * * * * */
void hamil::HamilA(const params &config, traj &curr_traj) {

  // update Ve
  HamilD(config, curr_traj);

  double V12_sq = real(Ve(0, 1) * Ve(1, 0));
  // double Tra = 0;
  double Det = real(Ve(0, 0) * Ve(1, 1) - V12_sq);

  eigs.zeros(config.qdim);
  // eigs(0) = 0.5*(Tra - std::sqrt(std::pow(Tra,2) - 4.0*Det));
  // eigs(1) = 0.5*(Tra + std::sqrt(std::pow(Tra,2) - 4.0*Det));
  eigs(0) = -std::sqrt(-Det);
  eigs(1) = std::sqrt(-Det);

  Ue.zeros(config.qdim, config.qdim);
  double wave_norm = std::sqrt(std::pow(real(eigs(0) - Ve(1, 1)), 2) + V12_sq);
  Ue(0, 0) = (eigs(0) - Ve(1, 1)) / wave_norm;
  Ue(1, 0) = Ve(1, 0) / wave_norm;
  wave_norm = std::sqrt(std::pow(real(eigs(1) - Ve(1, 1)), 2) + V12_sq);
  Ue(0, 1) = (eigs(1) - Ve(1, 1)) / wave_norm;
  Ue(1, 1) = Ve(1, 0) / wave_norm;

  curr_traj.F.zeros(config.cdim);

  return;
}

void hamil::set_params(const params &config) {
  jA = config.jA;
  jlx = config.jlx;
  jbx = config.jbx;
}
