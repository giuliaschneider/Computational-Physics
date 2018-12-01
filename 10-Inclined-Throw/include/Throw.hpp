
#ifndef THROW
#define THROW

#include <armadillo>

namespace comphys{

class Throw{
private:
  double gair;
  double v0;
  double t0;
  double tend;
  int n_steps;
  int i;
  char filename[160];
public:
  Throw();
  arma::vec F(arma::vec y, double t);
  void vary_gamma();
};
}

#endif
