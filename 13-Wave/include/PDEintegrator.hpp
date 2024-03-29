
#ifndef PDEINTEGRATOR
#define PDEINTEGRATOR

#include <armadillo>

namespace comphys{

class PDEintegrator{
private:
  int N;
  int n_innergrid;
  double atol;
  double dx;
  arma::vec psi;
  arma::vec b;
  std::string vfilename;
private:
  double update_psi(int position);
public:
  PDEintegrator(int N, arma::vec b, double atol, std::string vfilename);
  void Jacobi();
  void GaussSeidel();

};

}

#endif
