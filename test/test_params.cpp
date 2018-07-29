#include "params.h"
#include "gtest/gtest.h"

TEST(params, read_input) {

  params config;
  config.read_input("../test/reference_config.txt");

  EXPECT_EQ(config.ntrajs, 10);
  EXPECT_EQ(config.nsteps, 2);
  EXPECT_DOUBLE_EQ(config.dt, 0.25);
  EXPECT_DOUBLE_EQ(config.dt2, 0.25 / 2.0);

  EXPECT_EQ(config.qdim, 2);
  EXPECT_EQ(config.cdim, 2);
  EXPECT_DOUBLE_EQ(config.jA, 0.1);
  EXPECT_DOUBLE_EQ(config.jlx, 1.0);
  EXPECT_DOUBLE_EQ(config.jbx, 3.0);

  EXPECT_DOUBLE_EQ(config.phase, 2.0 * M_PI / 4.0);

  EXPECT_DOUBLE_EQ(config.sigx(0), 1.0);
  EXPECT_DOUBLE_EQ(config.sigx(1), 1.0);

  EXPECT_DOUBLE_EQ(config.sigp(0), 0.0);
  EXPECT_DOUBLE_EQ(config.sigp(1), 0.0);

  EXPECT_DOUBLE_EQ(config.x0(0), 0.0);
  EXPECT_DOUBLE_EQ(config.x0(1), -2.5);

  EXPECT_DOUBLE_EQ(config.p0(0), 0.0);
  EXPECT_DOUBLE_EQ(config.p0(1), 30);

  EXPECT_DOUBLE_EQ(two_pi, 2.0 * M_PI);

  EXPECT_EQ(config.seed, 550);
}
