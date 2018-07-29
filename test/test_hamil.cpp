#include "hamil.h"
#include "params.h"
#include "gtest/gtest.h"

TEST(hamil, set_params) {
  params config;
  config.read_input("../test/reference_config.txt");

  hamil curr_H;
  curr_H.set_params(config);

  EXPECT_DOUBLE_EQ(config.jA, curr_H.jA);
  EXPECT_DOUBLE_EQ(config.jlx, curr_H.jlx);
  EXPECT_DOUBLE_EQ(config.jbx, curr_H.jbx);
}

// FIXME
// Uncomment these expects, then run the tests. Each expect will fail and
// tell you what the value should have been. Then copy that number below

// TEST(hamil, HamilD) {
//   params config;
//   config.read_input("../test/reference_config.txt");
//
//   hamil curr_H;
//   curr_H.set_params(config);
//
//   traj curr_traj;
//   arma::arma_rng::set_seed(config.seed);
//   curr_traj.initial(config);
//
//   curr_H.HamilA(config, curr_traj);
//
//   EXPECT_NEAR(curr_H.Ve(0, 0), 0.0, 1.0E-8);
//   EXPECT_NEAR(curr_H.Ve(1, 1), 0.0, 1.0E-8);
//   EXPECT_NEAR(curr_H.Ve(0, 1), 0.0, 1.0E-8);
//   EXPECT_NEAR(curr_H.Ve(1, 0), 0.0, 1.0E-8);
//
//   EXPECT_NEAR(curr_H.Fe(0, 0, 0), 0.0, 1.0E-8);
//   EXPECT_NEAR(curr_H.Fe(1, 1, 0), 0.0, 1.0E-8);
//   EXPECT_NEAR(curr_H.Fe(0, 1, 0), 0.0, 1.0E-8);
//   EXPECT_NEAR(curr_H.Fe(1, 0, 0), 0.0, 1.0E-8);
//   EXPECT_NEAR(curr_H.Fe(0, 1, 1), 0.0, 1.0E-8);
//   EXPECT_NEAR(curr_H.Fe(1, 0, 1), 0.0, 1.0E-8);
// }

TEST(hamil, HamilA) {
  params config;
  config.read_input("../test/reference_config.txt");

  hamil curr_H;
  curr_H.set_params(config);

  traj curr_traj;
  arma::arma_rng::set_seed(config.seed);
  curr_traj.initial(config);

  // Set curr_traj.F != 0 so that we can make sure that HamilA is zeroing F
  for (int i = 0; i < config.cdim; ++i) {
    curr_traj.F(i) = 1.0;
  }

  curr_H.HamilA(config, curr_traj);

  // EXPECT_NEAR(curr_H.eigs(0), 0.0, 1.0E-8);
  // EXPECT_NEAR(curr_H.eigs(1), 0.0, 1.0E-8);
  //
  // EXPECT_NEAR(curr_H.Ue(0, 0), 0.0, 1.0E-8);
  // EXPECT_NEAR(curr_H.Ue(1, 1), 0.0, 1.0E-8);
  // EXPECT_NEAR(curr_H.Ue(0, 1), 0.0, 1.0E-8);
  // EXPECT_NEAR(curr_H.Ue(1, 0), 0.0, 1.0E-8);

  for (int i = 0; i < config.cdim; ++i) {
    EXPECT_DOUBLE_EQ(curr_traj.F(i), 0.0);
  }
}
