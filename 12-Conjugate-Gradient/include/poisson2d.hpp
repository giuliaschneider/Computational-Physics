
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
  double tol;
  double dx;
  arma::vec rho;
  arma::mat A;
  std::string method;
  std::string charge_distribution;
  std::string filename;
private:
  void set_rho();
public:
  poisson2d(int N, int n_charges, double* x0, double* y0, double tol, std::string method, std::string charge_distribution);
  ~poisson2d();
  void calc_Poisson();
};

}

#endif
