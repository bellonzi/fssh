#include "params.h"
#include "traj.h"
#include "gtest/gtest.h"

TEST(traj, initial) {
  params config;
  config.read_input("../test/reference_config.json");

  std::mt19937 prng;
  prng.seed(config.seed);

  traj curr_traj;
  curr_traj.initial(config, prng);

  EXPECT_NEAR(curr_traj.x(0), -0.29009427726390741, 1.0E-8);
  EXPECT_NEAR(curr_traj.x(1), -1.1784441699122719, 1.0E-8);

  EXPECT_NEAR(curr_traj.p(0), 0.0, 1.0E-8);
  EXPECT_NEAR(curr_traj.p(1), 30.0, 1.0E-8);

  EXPECT_NEAR(curr_traj.psi(0).real(), 0.70710678118654746, 1.0E-8);
  EXPECT_NEAR(curr_traj.psi(0).imag(), 0.0, 1.0E-8);
  EXPECT_NEAR(curr_traj.psi(1).real(), 0.0, 1.0E-8);
  EXPECT_NEAR(curr_traj.psi(1).imag(), 0.70710678118654757, 1.0E-8);

  EXPECT_EQ(curr_traj.surface, 0);

  EXPECT_NEAR((curr_traj.checknorm()).real(),1.0,1.0E-8);
  EXPECT_NEAR((curr_traj.checknorm()).imag(),0.0,1.0E-8);
}

TEST(traj, initial_zero) {
  params config;
  config.read_input("../test/reference_config.json");

  traj curr_traj;
  curr_traj.initial_zero(config);

  EXPECT_NEAR(curr_traj.x(0), 0.0, 1.0E-8);
  EXPECT_NEAR(curr_traj.x(1), 0.0, 1.0E-8);

  EXPECT_NEAR(curr_traj.p(0), 0.0, 1.0E-8);
  EXPECT_NEAR(curr_traj.p(1), 0.0, 1.0E-8);

  EXPECT_NEAR(curr_traj.psi(0).real(), 0.0, 1.0E-8);
  EXPECT_NEAR(curr_traj.psi(0).imag(), 0.0, 1.0E-8);
  EXPECT_NEAR(curr_traj.psi(1).real(), 0.0, 1.0E-8);
  EXPECT_NEAR(curr_traj.psi(1).imag(), 0.0, 1.0E-8);

  EXPECT_EQ(curr_traj.surface, 0);
}

TEST(traj, add_rk4) {
  params config;
  config.read_input("../test/reference_config.json");

  std::mt19937 prng;
  prng.seed(config.seed);

  traj curr_traj;
  curr_traj.initial(config, prng);

  rk4 curr_rk4(config);
  traj temp_traj = add_rk4(curr_traj, curr_rk4);

  EXPECT_NEAR(temp_traj.x(0), -0.29009427726390741, 1.0E-8);
  EXPECT_NEAR(temp_traj.x(1), -1.1784441699122719, 1.0E-8);

  EXPECT_NEAR(temp_traj.p(0), 0.0, 1.0E-8);
  EXPECT_NEAR(temp_traj.p(1), 30.0, 1.0E-8);

  EXPECT_NEAR(temp_traj.psi(0).real(), 0.70710678118654746, 1.0E-8);
  EXPECT_NEAR(temp_traj.psi(0).imag(), 0.0, 1.0E-8);
  EXPECT_NEAR(temp_traj.psi(1).real(), 0.0, 1.0E-8);
  EXPECT_NEAR(temp_traj.psi(1).imag(), 0.70710678118654757, 1.0E-8);

  EXPECT_EQ(temp_traj.surface, 0);

  curr_rk4.x(0) -= 1;
  curr_rk4.p += 1;

  temp_traj = add_rk4(curr_traj, curr_rk4);

  EXPECT_NEAR(temp_traj.x(0), -1.29009427726390741, 1.0E-8);
  EXPECT_NEAR(temp_traj.x(1), -1.1784441699122719, 1.0E-8);

  EXPECT_NEAR(temp_traj.p(0), 1.0, 1.0E-8);
  EXPECT_NEAR(temp_traj.p(1), 31.0, 1.0E-8);

  EXPECT_EQ(temp_traj.surface, 0);
}
