#include "hamil.h"
#include "traj.h"
#include "params.h"
#include "gtest/gtest.h"

TEST(hamil, set_params) {
  params config;
  config.read_input("../test/reference_config.json");

  hamil curr_H;
  curr_H.set_params(config);

  EXPECT_DOUBLE_EQ(config.jA, curr_H.jA);
  EXPECT_DOUBLE_EQ(config.jlx, curr_H.jlx);
  EXPECT_DOUBLE_EQ(config.jbx, curr_H.jbx);
  EXPECT_THROW(
      {
        try {
          config.qdim = 3;
          curr_H.set_params(config);
        } catch (std::exception &err) {
          EXPECT_STREQ("qdim must be 2 for this Hamiltonian",
                       err.what());
          throw std::exception();
        }
      },
      std::exception);
}

TEST(hamil, HamilD) {
  params config;
  config.read_input("../test/reference_config.json");

  hamil curr_H;
  curr_H.set_params(config);

  std::mt19937 prng;
  prng.seed(config.seed);

  traj curr_traj;
  curr_traj.initial(config, prng);

  curr_H.HamilA(curr_traj);

  EXPECT_NEAR(curr_H.Ve(0, 0).real(), 0.094172360229944088, 1.0E-8);
  EXPECT_NEAR(curr_H.Ve(1, 1).real(), -0.094172360229944088, 1.0E-8);
  EXPECT_NEAR(abs(curr_H.Ve(0, 1)), 0.033638765862047407, 1.0E-8);
  EXPECT_NEAR(abs(curr_H.Ve(1, 0)), 0.033638765862047407, 1.0E-8);

  EXPECT_NEAR(abs(curr_H.Fe(0, 0, 0)), 0.33807452152944378, 1.0E-8);
  EXPECT_NEAR(abs(curr_H.Fe(1, 1, 0)), 0.33807452152944378, 1.0E-8);
  EXPECT_NEAR(abs(curr_H.Fe(0, 1, 0)), 0.94644600686605007, 1.0E-8);
  EXPECT_NEAR(abs(curr_H.Fe(1, 0, 0)), 0.94644600686605007, 1.0E-8);
  EXPECT_NEAR(abs(curr_H.Fe(0, 0, 1)), 0.0, 1.0E-8);
  EXPECT_NEAR(abs(curr_H.Fe(1, 1, 1)), 0.0, 1.0E-8);
  EXPECT_NEAR(abs(curr_H.Fe(0, 1, 1)), 0.010091629758614221, 1.0E-8);
  EXPECT_NEAR(abs(curr_H.Fe(1, 0, 1)), 0.010091629758614221, 1.0E-8);
}

TEST(hamil, HamilA) {
  params config;
  config.read_input("../test/reference_config.json");

  hamil curr_H;
  curr_H.set_params(config);

  std::mt19937 prng;
  prng.seed(config.seed);

  traj curr_traj;
  curr_traj.initial(config, prng);

  curr_H.HamilA(curr_traj);

  EXPECT_NEAR(curr_H.eigs(0), -0.1, 1.0E-8);
  EXPECT_NEAR(curr_H.eigs(1), 0.1, 1.0E-8);
  EXPECT_NEAR(curr_H.eigs(0), -config.jA, 1.0E-8);
  EXPECT_NEAR(curr_H.eigs(1), config.jA, 1.0E-8);

  EXPECT_NEAR(abs(curr_H.Ue(0, 0)), 0.17069914718673779, 1.0E-8);
  EXPECT_NEAR(abs(curr_H.Ue(0, 1)), 0.98532319629130838, 1.0E-8);
  EXPECT_NEAR(abs(curr_H.Ue(1, 0)), 0.98532319629130838, 1.0E-8);
  EXPECT_NEAR(abs(curr_H.Ue(1, 1)), 0.17069914718673779, 1.0E-8);

  for (int i = 0; i < curr_H.cdim; ++i) {
    EXPECT_DOUBLE_EQ(curr_H.F(i), 0.0);
  }
}

TEST(hamil, checkE) {
  params config;
  config.read_input("../test/reference_config.json");

  std::mt19937 prng;
  prng.seed(config.seed);

  traj curr_traj;
  curr_traj.initial(config, prng);

  hamil curr_H;
  curr_H.set_params(config);

  curr_H.HamilA(curr_traj);

  EXPECT_NEAR(curr_H.checkE(curr_traj),449.89999999999998,1.0E-8);

}

