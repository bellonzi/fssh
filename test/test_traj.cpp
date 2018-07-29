#include "params.h"
#include "traj.h"
#include "gtest/gtest.h"

TEST(traj, initial) {
  params config;
  config.read_input("../test/reference_config.txt");

  arma::arma_rng::set_seed(config.seed);

  traj curr_traj;
  curr_traj.initial(config);

  EXPECT_NEAR(curr_traj.x(0), 0.52928799681641026, 1.0E-8);
  EXPECT_NEAR(curr_traj.x(1), -4.0473080479951768, 1.0E-8);

  EXPECT_NEAR(curr_traj.p(0), 0.0, 1.0E-8);
  EXPECT_NEAR(curr_traj.p(1), 30.0, 1.0E-8);

  EXPECT_NEAR(curr_traj.F(0), 0.0, 1.0E-8);
  EXPECT_NEAR(curr_traj.F(1), 0.0, 1.0E-8);

  EXPECT_NEAR(curr_traj.psi(0).real(), 0.70710678118654746, 1.0E-8);
  EXPECT_NEAR(curr_traj.psi(0).imag(), 0.0, 1.0E-8);
  EXPECT_NEAR(curr_traj.psi(1).real(), 0.0, 1.0E-8);
  EXPECT_NEAR(curr_traj.psi(1).imag(), 0.70710678118654757, 1.0E-8);

  EXPECT_EQ(curr_traj.surface, 1);
}
