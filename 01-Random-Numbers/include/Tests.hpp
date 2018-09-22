
#ifndef TESTS
#define TESTS

#include <armadillo>


class Tests {
private:
  int numberRNG;
  arma::vec countInterval(arma::vec &rdn_array, int k, long int rng_max);
  double calculateChi2(arma::vec &rdn_array, int k, long int rng_max);
public:
  void getHistogram(arma::vec &rdn_array, int k, long int rng_max);
  void getChi2(arma::vec &rdn_array, int k, long int rng_max);
  void compareRNG();
};


#endif
