#include "poisson2d.hpp"
#include "PDEintegrator.hpp"
#include <iostream>


using namespace std;

int main(){

  int N = 50;
  int n_charges = 1;
  double x0[1] = {0.75};
  double y0[1] = {0.75};

  poisson2d task1(N, n_charges, x0, y0);
  arma::vec rho = task1.get_rho();

  double atol = 0.00001;
  char filename[160];

  /*
  Task 1
  */
  sprintf(filename,"results/cg_charges_%d.txt",n_charges);
  cg cgIntegrator(N, rho, atol, filename);
  cgIntegrator.integrate();




  return 0;
}
