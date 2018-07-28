#include "lib.h"

//set global variables
int ntrajs,nsteps;
double dt,dt2;
int qdim, cdim;
double phase;
arma::vec sigx, sigp;
arma::vec x0, p0;
double jA, jlx, jbx;

/* * * * * * * * * * * * * * * * * * * * * * * */
void read_input (void) {

  size_t pos;
  std::string delim1 = "\t";
  std::ifstream input("run.in");
  std::string line;

  getline( input, line ); //!calculation
  getline( input, line ); //ntrajs
  pos = line.find(delim1);
  ntrajs = stoi(line.substr(0, pos));
  getline( input, line ); //nsteps
  pos = line.find(delim1);
  nsteps = stoi(line.substr(0, pos));
  getline( input, line ); //dt
  pos = line.find(delim1);
  dt = stod(line.substr(0, pos));
  dt2 = dt/2;

  getline( input, line ); //!Hamil
  getline( input, line ); //qdim
  pos = line.find(delim1);
  qdim = stoi(line.substr(0, pos));
  if (qdim != 2) {
    std::cout << "Only works for qdim = 2.\n Change system." << std::endl;
    std::exit(EXIT_FAILURE); 
  }
  getline( input, line ); //cdim
  pos = line.find(delim1);
  cdim = stoi(line.substr(0, pos));
  getline( input, line ); //jA
  pos = line.find(delim1);
  jA = stod(line.substr(0, pos));
  getline( input, line ); //jlx
  pos = line.find(delim1);
  jlx = stod(line.substr(0, pos));
  std::cout << jlx << std::endl;
  getline( input, line ); //jbx
  pos = line.find(delim1);
  jbx = stod(line.substr(0, pos));
  std::cout << jbx << std::endl;

  sigx.zeros(cdim);
  sigp.zeros(cdim);
  x0.zeros(cdim);
  p0.zeros(cdim);

  getline( input, line ); //!initial
  getline( input, line ); //phase = 2pi/x
  pos = line.find(delim1);
  phase = two_pi/stod(line.substr(0, pos));
  getline( input, line ); //sigx
  for(int ic = 0; ic < cdim; ic++){
    pos = line.find(delim1);
    sigx(ic) = stod(line.substr(0, pos));
    line.erase(0, pos + delim1.length());
  }
  if (line!= "!sigx") {
    std::cout << "Sig_x is not the right size.\n cdim = " << cdim <<  std::endl;
    std::exit(EXIT_FAILURE); 
  }
  getline( input, line ); //x0
  for(int ic = 0; ic < cdim; ic++){
    pos = line.find(delim1);
    x0(ic) = stod(line.substr(0, pos));
    line.erase(0, pos + delim1.length());
  }
  getline( input, line ); //p0
  for(int ic = 0; ic < cdim; ic++){
    pos = line.find(delim1);
    p0(ic) = stod(line.substr(0, pos));
    line.erase(0, pos + delim1.length());
  }

  //seed random number generator
  getline( input, line ); //cdim
  pos = line.find(delim1);
  int seed = stoi(line.substr(0, pos));
  std::srand(seed);

  return;
}

/* * * * * * * * * * * * * * * * * * * * * * * */
void boxmuller (arma::vec& randvec) {
  double epsilon = std::numeric_limits<double>::min();
  double u1, u2;
  int lrand = 1;
  do{
    do
     {
       u1 = rand() * (1.0 / RAND_MAX);
       u2 = rand() * (1.0 / RAND_MAX);
     }
    while ( u1 <= epsilon );
    
    randvec[lrand-1] = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
    randvec[ lrand ] = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
    lrand += 2;
  } while ( lrand <= randvec.n_elem );

  return;
}

