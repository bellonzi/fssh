#include "hamil.h"
#include "lib.h"
#include "traj.h"
#include <ctime>

namespace fssh {
/* * * * * * * * * * * * * * * * * * * * * * * */
void propagate(traj &curr_traj) {
  // x + p/m*dt/2
  curr_traj.x = curr_traj.x + curr_traj.p * dt2;

  // update Hamil to get Fsurf
  hamil::HamilA(curr_traj);
  // p + F*dt
  curr_traj.p = curr_traj.p + curr_traj.F * dt;

  // x + p/m*dt/2
  curr_traj.x = curr_traj.x + curr_traj.p * dt2;

  return;
}
} // namespace fssh

/***********************************************/
int main() {

  const clock_t begin_time = std::clock();

  read_input();

  for (int itraj = 0; itraj < ::ntrajs; itraj++) {
    traj curr_traj;
    curr_traj.initial();

    for (int istep = 0; istep < nsteps; istep++) {
      fssh::propagate(curr_traj);
    }
    std::cout << "traj: " << itraj << std::endl;
  }

  std::cout << "This calculation took "
            << float(std::clock() - begin_time) / CLOCKS_PER_SEC << " secs."
            << std::endl;

  return 0;
}
