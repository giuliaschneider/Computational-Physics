/**
  CS-11
  @file     PDEintegrator.cpp
  @author   Giulia Schneider
  @date     26.06.2018
  *version  1.0
  @brief    Generates a
*/

#include "PDEintegrator.hpp"
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>


using namespace std;



namespace comphys{

PDEintegrator::PDEintegrator(int N, arma::vec &b,  double tol, string vfilename):
  N(N), b(b), tol(tol), vfilename(vfilename) {

    dx = 1.0/N;
    n_innergrid = N-2;

    setA();
    initalizePsi();
    conjugateGradient();
  }

void PDEintegrator::setA(){
  cout << "Setting A" << endl;
  A.set_size((n_innergrid*n_innergrid), (n_innergrid*n_innergrid));
  A.diag().fill(-4);
  A.diag(-1).fill(1);
  A.diag(1).fill(1);
  A.diag(-3).fill(1);
  A.diag(3).fill(1);
}

void PDEintegrator::initalizePsi(){
  psi.set_size((N-2)*(N-2));
  psi.randu();
  r = b - A*psi;
  d = r;
}

void PDEintegrator::gradientStep(){

  c = 1.0/as_scalar(d.st()*A*d);
  alpha = c*as_scalar(r.st()*d);
  psi += alpha*d;
  r = b - A*psi;
  d = r - (c*as_scalar(r.st()*A*d)) * d;


}

void PDEintegrator::conjugateGradient(){
  int i = 0;
  while(as_scalar(r.st()*r) >= tol){
    cout << "Iteration = " << i << endl;
    cout << "Psi = " << psi.st() << endl;
    gradientStep();
    i++;
  }
  psi.save(vfilename,arma::raw_ascii);
}

}
