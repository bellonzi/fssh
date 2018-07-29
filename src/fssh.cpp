#include "lib.h"
#include <ctime>

namespace fssh {
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
} // namespace fssh

/***********************************************/
int main() {

  const clock_t begin_time = std::clock();

  read_input();

  for (int itraj = 0; itraj < ::ntrajs; itraj++) {
    traj curr_traj;
    curr_traj.initial();

    for (int istep = 0; istep < nsteps; istep++) {
      fssh::propagate();
    }
    std::cout << "traj: " << itraj << std::endl;
  }

  std::cout << "This calculation took "
            << float(std::clock() - begin_time) / CLOCKS_PER_SEC << " secs."
            << std::endl;

  return 0;
}
