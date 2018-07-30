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
