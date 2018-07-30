#include <fstream>
#include <iterator>

#include "json.hpp"
#include "params.h"
#include "gtest/gtest.h"

TEST(nlohmann_json, read_string_directly) {

  nlohmann::json j =
      "{\"type\": \"attempt at json\", \"lunch\": \"spam\"}"_json;
  EXPECT_TRUE(j["type"] == std::string("attempt at json"));
  EXPECT_TRUE(j["lunch"] == "spam");
}

TEST(nlohmann_json, read_string_from_file) {

  std::ifstream file("../test/stringify_example.json");
  nlohmann::json j;
  file >> j;
  EXPECT_TRUE(j["type"] == std::string("attempt at json"));
  EXPECT_TRUE(j["lunch"] == "spam");
}

TEST(nlohmann_json, read_numbers_from_file) {

  std::ifstream file("../test/numeric_example.json");
  nlohmann::json j;
  file >> j;
  EXPECT_EQ(j["nsteps"], 100);
  EXPECT_DOUBLE_EQ(j["x"][0], 0.1);
  EXPECT_DOUBLE_EQ(j["x"][1], 1.0);
  EXPECT_DOUBLE_EQ(j["p"][0], -1.0);
  EXPECT_DOUBLE_EQ(j["p"][1], 30.0);
}
