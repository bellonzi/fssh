#include "hamil.h"
#include "params.h"
#include "traj.h"

namespace fssh {

void propagate(const params &, traj &, hamil &);

void update_dcdt(arma::cx_vec &, const traj &, const hamil &);
} // namespace fssh
