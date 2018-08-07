#include <ctime>

#include "fssh.h"
#include "hamil.h"
#include "params.h"
#include "traj.h"

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
    curr_H.HamilA(curr_traj);

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
