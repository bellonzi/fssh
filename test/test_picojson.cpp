#include <fstream>
#include <iterator>

#include "params.h"
#include "picojson/picojson.h"
#include "gtest/gtest.h"

TEST(picojson, read_string) {

  std::string json = "{\"type\": \"attempt at json\", \"lunch\": \"spam\"}";
  picojson::value v;
  std::string err = picojson::parse(v, json);
  EXPECT_TRUE(err.empty());
  // std::cout << v << std::endl;
  // std::cout << v.get<picojson::object>()["type"] << std::endl;
  EXPECT_TRUE(v.is<picojson::object>());
  EXPECT_TRUE(v.get<picojson::object>()["type"].get<std::string>() ==
              std::string("attempt at json"));
  EXPECT_TRUE(v.get<picojson::object>()["lunch"].get<std::string>() == "spam");
  // if (!err.empty()) {
  //   std::cerr << err << std::endl;
  // }

  // Declaration
  // std::ifstream f("example.json");
  // std::istream_iterator<std::string> input(f);
  //
  // picojson::value v;
  // std::string err;
  // input = picojson::parse(v, input, std::istream_iterator<std::string>(),
  // &err); if (!err.empty()) {
  //   std::cerr << err << std::endl;
  // }

  // EXPECT_TRUE(v.is<picojson::object>());
  // picojson::object &o =
  //     v.get<picojson::object>()["Test1"].get<picojson::object>();
  // cout << "TestInt: " << o["TestInt"].get<double>() << endl;
  // cout << "TestDbl: " << o["TestDbl"].get<double>() << endl;
  // cout << "TestStr: " << o["TestStr"].get<string>() << endl;
  // cout << "TestBln: " << o["TestBln"].get<bool>() << endl;
  // array &aAry = o["TestAry"].get<array>();
  // cout << "TestAry:" << endl;
  // for (i = 0; i < aAry.size(); i++)
  //   cout << "\t" << aAry[i].get<string>() << endl;
}
