#include <ctime>

#include "hamil.h"
#include "params.h"
#include "traj.h"

namespace fssh {

void propagate(const params &config, traj &curr_traj, hamil &curr_H) {
  // x + p/m*dt/2
  curr_traj.x = curr_traj.x + curr_traj.p * config.dt2;

  // update Hamil to get Fsurf
  curr_H.HamilA(config, curr_traj);
  // p + F*dt
  curr_traj.p = curr_traj.p + curr_traj.F * config.dt;

  // x + p/m*dt/2
  curr_traj.x = curr_traj.x + curr_traj.p * config.dt2;

  return;
}

} // namespace fssh

/***********************************************/
int main() {

  const clock_t begin_time = std::clock();

  params config;
  config.read_input("run.in");
  hamil curr_H;
  curr_H.set_params(config);

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
