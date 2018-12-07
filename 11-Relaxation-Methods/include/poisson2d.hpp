
#ifndef POISSON2D
#define POISSON2D

#include <armadillo>


class poisson2d{
private:
  int N;
  int n_innergrid;
  int n_charges;
  double* x0;
  double* y0;
  arma::vec rho;
private:
  void set_rho();
public:
  poisson2d(int N, int n_charges, double* x0, double* y0);
  arma::vec get_rho();
};


#endif
