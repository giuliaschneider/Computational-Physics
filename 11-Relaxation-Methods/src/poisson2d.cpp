/**
  CS-11
  @file     poisson2d.cpp
  @author   Giulia Schneider
  @date     07.12.2018
  *version  1.0
  @brief    Wraps up the parameters and right hand side function
            of the 2D poisson equation.
*/

#include "poisson2d.hpp"
#include "PDEintegrator.hpp"
#include <iostream>



using namespace std;



poisson2d::poisson2d(int N, int n_charges, double* x0, double* y0):
  N(N), n_charges(n_charges), x0(x0), y0(y0){
    n_innergrid = N-2;
    set_rho();
  }



void poisson2d::set_rho(){
  /**
  * Calculates the right-hand side vector
  * Return void
  */
  rho.set_size(n_innergrid*n_innergrid);

  for(int icharge=0; icharge<n_charges; icharge++){
    int i = int(x0[icharge]*n_innergrid);
    int j = int(y0[icharge]*n_innergrid);
    int k_charge = i + (j-1)*n_innergrid;
    rho[k_charge] = -0.25;
  }
}

arma::vec poisson2d::get_rho(){
  /**
  * Return right-hand side vector
  */
  return rho;
}
