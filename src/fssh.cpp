#include <ctime>

#include "hamil.h"
#include "params.h"
#include "traj.h"

namespace fssh {

void propagate(const params &config, traj &curr_traj, hamil &curr_H) {
  // t_{n+1}= t_{n} + dt
  rk4 k1(config), k2(config), k3(config), k4(config);
  traj temp_traj;
  temp_traj.initial_zero(config);
  arma::cx_vec dcdt(config.qdim); 

  // k_{1}=0.5 dt f(t_{n}, y_{n})
  curr_H.HamilA(config, curr_traj);
  k1.x =   config.dt2 * curr_traj.p;
  k1.p =   config.dt2 * curr_H.F;

  dcdt.zeros();
  for(int i = 0; i<config.qdim; i++){
     dcdt(i) -= arma::cx_double(0,1)*curr_traj.psi(i)*curr_H.eigs(i);
     for(int j = 0; j<config.qdim; j++){
        if(j!=i){
          arma::cx_vec temp_dij = curr_H.dij(arma::span(i),arma::span(j),arma::span::all);
          dcdt(i) -= curr_traj.psi(j)*dot(curr_traj.p,temp_dij);
     }
     }
  }

  //k1.psi = config.dt2 * dcdt;

  // k_{2}=0.5 dt f(t_{n} + dt/2, y_{n} + k_{1})
  temp_traj = add_rk4(curr_traj, k1);
  curr_H.HamilA(config, temp_traj);
  k2.x = config.dt2 * temp_traj.p;
  k2.p = config.dt2 * curr_H.F;

  // k_{3}=dt f(t_{n} + dt/2, y_{n} + k_{2})
  temp_traj = add_rk4(curr_traj, k2);
  curr_H.HamilA(config, temp_traj);
  k3.x = config.dt * temp_traj.p;
  k3.p = config.dt * curr_H.F;

  // k_{4}=dt f(t_{n} + dt, y_{n} + k_{3})
  temp_traj = add_rk4(curr_traj, k3);
  curr_H.HamilA(config, temp_traj);
  k4.x = config.dt * temp_traj.p;
  k4.p = config.dt * curr_H.F;

  // y_{n+1}= y_{n} + 1/6 (2 k_{1} + 4 k_{2} + 2 k_{3} + k_{4})
  curr_traj.x = curr_traj.x + (2 * k1.x + 4 * k2.x + 2 * k3.x + k4.x) / 6;
  curr_traj.p = curr_traj.p + (2 * k1.p + 4 * k2.p + 2 * k3.p + k4.p) / 6;
  curr_traj.psi =
      curr_traj.psi + (2 * k1.psi + 4 * k2.psi + 2 * k3.psi + k4.psi) / 6;

  curr_H.HamilA(config, curr_traj);

  // call hop_or_not

  return;
}

} // namespace fssh

/***********************************************/
int main() {

  const clock_t begin_time = std::clock();

  params config;
  config.read_input("run.json");
  hamil curr_H;
  try {
    curr_H.set_params(config);
  } catch (std::exception &err) {
    std::cerr << err.what() << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::mt19937 prng;
  prng.seed(config.seed);

  for (int itraj = 0; itraj < config.ntrajs; itraj++) {

    traj curr_traj;
    curr_traj.initial(config, prng);
    curr_H.HamilA(config, curr_traj);

    for (int istep = 0; istep < config.nsteps; istep++) {
      fssh::propagate(config, curr_traj, curr_H);
    }
    std::cout << "traj: " << itraj << std::endl;
  }

  std::cout << "This calculation took "
            << float(std::clock() - begin_time) / CLOCKS_PER_SEC << " secs."
            << std::endl;

  return 0;
}
