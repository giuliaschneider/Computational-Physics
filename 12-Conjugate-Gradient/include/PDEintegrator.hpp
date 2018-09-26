
#ifndef PDEINTEGRATOR
#define PDEINTEGRATOR

#include <armadillo>

namespace comphys{

class PDEintegrator{
private:
  int N;
  int n_innergrid;
  double tol;
  double dx;

  arma::vec psi;
  arma::vec b;
  arma::mat A;
  arma::vec r;
  arma::vec d;
  double c;
  double alpha;
  std::string vfilename;
private:
  double update_psi(int position);
public:
  PDEintegrator(int N, arma::vec &b, double tol, std::string vfilename);
  void setA();
  void initalizePsi();
  void gradientStep();
  void conjugateGradient();
  void Jacobi();
  void GaussSeidel();


};

}

#endif
