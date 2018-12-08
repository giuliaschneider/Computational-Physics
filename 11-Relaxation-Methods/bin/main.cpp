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
  sprintf(filename,"results/jacobi_n_charges_%d.txt",n_charges);
  Jacobi jacobiIntegrator(N, rho, atol, filename);
  jacobiIntegrator.integrate();

  /*
  Task 2
  */
  sprintf(filename,"results/gauss_seidel_n_charges_%d.txt",n_charges);
  GaussSeidel gaussIntegrator(N, rho, atol, filename);
  gaussIntegrator.integrate();

  /*
  Task 3
  */
  n_charges = 3;

  double x[3] = {0.2, 0.6, 0.75};
  double y[3] = {0.8, 0.1, 0.75};
  poisson2d task2(N, n_charges, x, y);
  rho = task2.get_rho();

  sprintf(filename,"results/jacobi_n_charges_%d.txt",n_charges);
  Jacobi jacobiIntegrator2(N, rho, atol, filename);
  jacobiIntegrator2.integrate();

  sprintf(filename,"results/gauss_seidel_n_charges_%d.txt",n_charges);
  GaussSeidel gaussIntegrator2(N, rho, atol, filename);
  gaussIntegrator2.integrate();

  return 0;
}
