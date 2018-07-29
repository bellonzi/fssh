#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <string>

#include "params.h"

// // set global variables
// int ntrajs, nsteps;
// double dt, dt2;
// int qdim, cdim;
// double phase;
// arma::vec sigx, sigp;
// arma::vec x0, p0;
// double jA, jlx, jbx;

/* * * * * * * * * * * * * * * * * * * * * * * */
void params::read_input(void) {

  size_t pos;
  std::string delim1 = "\t";
  std::ifstream input("run.in");
  std::string line;

  getline(input, line); //! calculation
  getline(input, line); // ntrajs
  pos = line.find(delim1);
  ntrajs = stoi(line.substr(0, pos));
  getline(input, line); // nsteps
  pos = line.find(delim1);
  nsteps = stoi(line.substr(0, pos));
  getline(input, line); // dt
  pos = line.find(delim1);
  dt = stod(line.substr(0, pos));
  dt2 = dt / 2;

  getline(input, line); //! Hamil
  getline(input, line); // qdim
  pos = line.find(delim1);
  qdim = stoi(line.substr(0, pos));
  if (qdim != 2) {
    std::cout << "Only works for qdim = 2.\n Change system." << std::endl;
    std::exit(EXIT_FAILURE);
  }
  getline(input, line); // cdim
  pos = line.find(delim1);
  cdim = stoi(line.substr(0, pos));
  getline(input, line); // jA
  pos = line.find(delim1);
  jA = stod(line.substr(0, pos));
  getline(input, line); // jlx
  pos = line.find(delim1);
  jlx = stod(line.substr(0, pos));
  std::cout << jlx << std::endl;
  getline(input, line); // jbx
  pos = line.find(delim1);
  jbx = stod(line.substr(0, pos));
  std::cout << jbx << std::endl;

  sigx.zeros(cdim);
  sigp.zeros(cdim);
  x0.zeros(cdim);
  p0.zeros(cdim);

  getline(input, line); //! initial
  getline(input, line); // phase = 2pi/x
  pos = line.find(delim1);
  phase = two_pi / stod(line.substr(0, pos));
  getline(input, line); // sigx
  for (int ic = 0; ic < cdim; ic++) {
    pos = line.find(delim1);
    sigx(ic) = stod(line.substr(0, pos));
    line.erase(0, pos + delim1.length());
  }
  if (line != "!sigx") {
    std::cout << "Sig_x is not the right size.\n cdim = " << cdim << std::endl;
    std::exit(EXIT_FAILURE);
  }
  getline(input, line); // x0
  for (int ic = 0; ic < cdim; ic++) {
    pos = line.find(delim1);
    x0(ic) = stod(line.substr(0, pos));
    line.erase(0, pos + delim1.length());
  }
  getline(input, line); // p0
  for (int ic = 0; ic < cdim; ic++) {
    pos = line.find(delim1);
    p0(ic) = stod(line.substr(0, pos));
    line.erase(0, pos + delim1.length());
  }

  // Get the seed for the random number generator
  getline(input, line); // cdim
  pos = line.find(delim1);
  seed = stoi(line.substr(0, pos));

  return;
}
