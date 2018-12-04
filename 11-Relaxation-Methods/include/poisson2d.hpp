
#ifndef POISSON2D
#define POISSON2D

#include <armadillo>

namespace comphys{

class poisson2d{
private:
  int N;
  int n_innergrid;
  int n_charges;
  double* x0;
  double* y0;
  double atol;
  double dx;
  arma::vec rho;
  char* method;
private:
  void set_rho();
public:
  poisson2d(int N, int n_charges, double* x0, double* y0, double atol, char* method);
  ~poisson2d();
};

}

#endif
