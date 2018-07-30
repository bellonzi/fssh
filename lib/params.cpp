#include <cstdlib>
#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"

#include "params.h"

void params::read_input(const std::string &input_file) {

  std::ifstream file(input_file);
  nlohmann::json j;
  file >> j;

  ntrajs = j["ntrajs"];
  nsteps = j["nsteps"];
  dt = j["dt"];
  dt2 = dt / 2;

  qdim = j["Hamil"]["qdim"];
  if (qdim != 2) {
    std::cout << "Only works for qdim = 2.\n Change system." << std::endl;
    std::exit(EXIT_FAILURE);
  }

  cdim = j["Hamil"]["cdim"];
  jA = j["Hamil"]["jA"];
  jlx = j["Hamil"]["jlx"];
  jbx = j["Hamil"]["jbx"];

  sigx.zeros(cdim);
  sigp.zeros(cdim);
  x0.zeros(cdim);
  p0.zeros(cdim);

  double phase_fac(j["init"]["phase_fac"]);
  phase = 0.0;
  if (phase_fac != 0.0) {
    phase = two_pi / phase_fac;
  }

  for (int ic = 0; ic < cdim; ic++) {
    sigx(ic) = j["init"]["sigx"][ic];
    x0(ic) = j["init"]["x0"][ic];
    p0(ic) = j["init"]["p0"][ic];
  }

  seed = j["seed"];
}
