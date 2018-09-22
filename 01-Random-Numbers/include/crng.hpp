

#ifndef CRNG
#define CRNG

#include <armadillo>


void uniform_circle(int numberRNG);


class crng {
private:
  int numberRNG;
  unsigned long int rdn;
  int c;
  int p;
  arma::vec rdn_array;

public:
  int rng_max;


private:
  int generateNumber(unsigned long int rdn);
  void generateSequence();

public:
  crng(int numberRNG, int p, int c, int seed);
  arma::vec getSequence();
};


#endif
