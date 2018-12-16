/**
  CS-11
  @file     cg.cpp
  @author   Giulia Schneider
  @date     16.12.2018
  *version  1.0
  @brief    Generates a
*/

#include "PDEintegrator.hpp"
#include <iostream>


using namespace std;


cg::cg(int N, arma::vec b, double atol, string vfilename):
  PDEintegrator(N, b, atol, vfilename){
    r = b - A*psi;
    d = r;
    maxIter = 1000;
    err.set_size(maxIter);
    err.fill(0.0);
    setA();
    setP();
  }

void cg::setA(){
  /**
  Sets matrix A
  Return void
  */
  arma::mat D(n_innergrid, n_innergrid);
  D.fill(0);
  D.diag().fill(-4); D.diag(-1).fill(1); D.diag(1).fill(1);

  A.eye(n_innergrid, n_innergrid);
  A = kron(A,D);
  A.diag(-n_innergrid).fill(1); A.diag(n_innergrid).fill(1);
  cout << A << endl;
}

void cg::setP(){
  /**
  Sets preconditioning matrix P
  Return void
  */
  P = diagmat(A)/(A(1,1)*A(1,1));
  A = P*A;
  b = P*b;
}

void cg::step(){
  /**
  Performs one conjugate gradient step
  Return void
  */
  c = 1.0/arma::as_scalar(d.st()*A*d);
  alpha = c*arma::as_scalar(r.st()*d);
  psi += alpha*d;
  r = b - A*psi;
  d = r - (c*arma::as_scalar(r.st()*A*d)) * d;
}

void cg::integrate(){
  /**
  * Integrates an elliptic PDE up to tolerance atol and save results to text
  */
  delta = 100.0;
  int numit = 0;
  while(delta >= atol and numit < maxIter){
    numit++;
    step();
    err(numit) = arma::as_scalar(r.st()*r);
  }
  cout << "Done after "<< numit << "iterations" << endl;
  psi.save(vfilename,arma::raw_ascii);
  err = err.head(numit);
  vfilename.erase (vfilename.end()-4, vfilename.end());
  vfilename += "_err.txt";
  err.save(vfilename, arma::raw_ascii);
}
