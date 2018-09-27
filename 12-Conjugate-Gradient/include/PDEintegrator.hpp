
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
  arma::mat P;
  double c;
  double alpha;
  double err = 100;
  std::string vfilename;
private:
  double update_psi(int position);
public:
  PDEintegrator(int N, arma::vec &b, double tol, std::string vfilename);
  void setA();
  void setP();
  void initalizePsi();
  void gradientStep();
  void conjugateGradient(bool precondition, int maxIter);
  void Jacobi();
  void GaussSeidel();


};

}

#endif
