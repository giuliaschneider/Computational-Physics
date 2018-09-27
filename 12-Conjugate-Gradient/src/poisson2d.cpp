/**
  CS-11
  @file     poisson2d.cpp
  @author   Giulia Schneider
  @date     26.06.2018
  *version  1.0
  @brief    Generates a
*/

#include "poisson2d.hpp"
#include "PDEintegrator.hpp"
#include <iostream>
#include <sstream>
#include <math.h>
#include <cmath>
#include <vector>


using namespace std;



namespace comphys{

poisson2d::poisson2d(int N, int n_charges, double* x0, double* y0, double tol, string method, string charge_distribution):
  N(N), n_charges(n_charges), tol(tol), x0(x0), y0(y0), method(method), charge_distribution(charge_distribution){
    dx = 1.0/N;
    n_innergrid = N-2;
    set_rho();
  }

poisson2d::~poisson2d(){
}

void poisson2d::set_rho(){
  /**
    @brief: calculates the charge density
    @param y: variables at current time step
    @param t: current time step
    @return arma::vec right hand side function of y' = f(y)
*/
  rho.set_size(n_innergrid*n_innergrid);
  if(charge_distribution=="point charge"){
    for(int icharge=0;icharge<n_charges;icharge++){
      int i = int(x0[icharge]*n_innergrid);
      int j = int(y0[icharge]*n_innergrid);
      int k_charge = i + (j-1)*n_innergrid;
      cout << "kcharge = " << k_charge << endl;
      rho[k_charge] = -0.25;
    }
  }
  else if(charge_distribution=="homogeneous"){
    rho.fill(1*dx*dx);
  }
  else{
    rho.fill(0);
  }

  //cout << rho << endl;
}

void poisson2d::calc_Poisson(){
  cout << "N = " << N << endl;
  cout << "Atol = " << tol << endl;
  if(method=="Jacobi"){
    filename =  "results/Jacobi_ncharge_1_05.txt";
    PDEintegrator integrator(N, rho, tol, filename);
    integrator.Jacobi();
  }
  else if(method=="Gauss Seidel"){
    filename =  "results/GaussSeidel_ncharge_1_05.txt";
    PDEintegrator integrator(N, rho, tol, filename);
    integrator.GaussSeidel();
  }
  else if(method=="Conjugate gradient"){
    filename =  "results/Gradient_w0pre";
    PDEintegrator integrator(N, rho, tol, filename);
    integrator.conjugateGradient(false, 500);

    filename =  "results/Gradient_wpre";
    PDEintegrator integrator2(N, rho, tol, filename);
    integrator2.conjugateGradient(true, 500);
  }
}


}
