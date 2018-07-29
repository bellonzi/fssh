#include "hamil.h"
#include "lib.h"
#include "traj.h"
#include <ctime>

namespace fssh {
/* * * * * * * * * * * * * * * * * * * * * * * */
void propagate(traj &curr_traj, hamil &curr_H) {
  // x + p/m*dt/2
  curr_traj.x = curr_traj.x + curr_traj.p * dt2;

  // update Hamil to get Fsurf
  curr_H.HamilA(curr_traj);
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
  hamil curr_H;

  for (int itraj = 0; itraj < ::ntrajs; itraj++) {
    traj curr_traj;
    curr_traj.initial();
    curr_H.HamilA(curr_traj);

    for (int istep = 0; istep < nsteps; istep++) {
      fssh::propagate(curr_traj, curr_H);
    }
    std::cout << "traj: " << itraj << std::endl;
  }

  std::cout << "This calculation took "
            << float(std::clock() - begin_time) / CLOCKS_PER_SEC << " secs."
            << std::endl;

  return 0;
}
