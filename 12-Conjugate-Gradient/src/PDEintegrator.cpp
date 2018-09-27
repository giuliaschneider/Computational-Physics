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

    cout << "tol = " << tol << endl;
  }

void PDEintegrator::setA(){
  cout << "Setting A" << endl;
  arma::mat D(n_innergrid, n_innergrid);
  D.fill(0);
  D.diag().fill(-4); D.diag(-1).fill(1); D.diag(1).fill(1);

  A.eye(n_innergrid, n_innergrid);
  A = kron(A,D);
  A.diag(-n_innergrid).fill(1); A.diag(n_innergrid).fill(1);
  //cout << A << endl;
}

void PDEintegrator::setP(){
  P = diagmat(A)/(A(1,1)*A(1,1));
  //cout << P << endl;
  A = P*A;
  b = P*b;
}

void PDEintegrator::initalizePsi(){
  psi.set_size((N-2)*(N-2));
  psi.fill(0.0);
  r = b - A*psi;
  d = r;
}

void PDEintegrator::gradientStep(){

  c = 1.0/as_scalar(d.st()*A*d);
  alpha = c*as_scalar(r.st()*d);
  psi += alpha*d;
  r = b - A*psi;
  d = r - (c*as_scalar(r.st()*A*d)) * d;
  err = as_scalar(r.st()*r);

}

void PDEintegrator::conjugateGradient(bool precondition, int maxIter){

  int i = 0;
  setA();
  initalizePsi();
  if(precondition){
    setP();
  }

  arma::vec errVector(maxIter,arma::fill::zeros);
  while( err >= tol and i < maxIter){
    cout << "Iteration = " << i << endl;
    //cout << "Psi = " << psi.st() << endl;
    errVector(i) = err;
    gradientStep();
    i++;
  }
  psi.save(vfilename+".txt",arma::raw_ascii);
  arma::vec errToSave = errVector.head(i);
  errToSave.save(vfilename+"_err.txt", arma::raw_ascii);
}



double PDEintegrator::update_psi(int position){
  if(position==0){ //upper-left corner
    return 0.25*(psi(position+1)+psi(position+n_innergrid)) - b(position);
  }
  else if(position==n_innergrid-1){ //upper-right corner
    return 0.25*(psi(position-1)+psi(position+n_innergrid)) - b(position);
  }
  else if(position==n_innergrid*n_innergrid-n_innergrid){ //lower-left corner
    return 0.25*(psi(position+1)+psi(position-n_innergrid)) - b(position);
  }
  else if(position==n_innergrid*n_innergrid-1){
    return 0.25*(psi(position-1)+psi(position-n_innergrid)) - b(position);
  }
  else if(position <= n_innergrid-1){ // upper boundary
    return 0.25*(psi(position-1)+psi(position+1)+psi(position+n_innergrid)) - b(position);
  }
  else if(position >= n_innergrid*n_innergrid-n_innergrid){ // lower boundary
    return 0.25*(psi(position-1)+psi(position+1)+psi(position-n_innergrid)) - b(position);
  }
  else if(position%n_innergrid==0){ // left boundary
    return 0.25*(psi(position+1)+psi(position-n_innergrid)+psi(position+n_innergrid)) - b(position);
  }
  else if(position%n_innergrid==n_innergrid-1){// right boundary
    return 0.25*(psi(position-1)+psi(position-n_innergrid)+psi(position+n_innergrid)) - b(position);
  }
  else{
    return 0.25*(psi(position-1)+psi(position+1)+psi(position-n_innergrid)+psi(position+n_innergrid)) - b(position);
  }
}

void PDEintegrator::Jacobi(){
  cout << "Jacobi method" << endl;
  arma::vec psi_new((N-2)*(N-2),arma::fill::zeros);
  double delta = 100.0;
  int numit = 0;
  while(delta >= tol){
    numit++;
    for(int i=0;i<(N-2)*(N-2);i++){
      psi_new(i) = update_psi(i);
    }
    delta = arma::norm(psi_new-psi)/arma::norm(psi);
    psi = psi_new;
    //cout << numit << ".Iteration" << endl;
  }
  psi.save(vfilename,arma::raw_ascii);
}

void PDEintegrator::GaussSeidel(){
  cout << "Gauss Seidel " << endl;
  double delta = 100.0;
  int numit = 0;
  double psi_norm = 0.0;
  double psi_n_psi_norm = 0.0;
  double psi_new = 0.0;
  while(delta >= tol){
    numit++;
    psi_norm = arma::norm(psi);
    psi_n_psi_norm = 0.0;
    for(int i=0;i<(N-2)*(N-2);i++){
       psi_new = update_psi(i);
       psi_n_psi_norm += pow(psi_new-psi(i),2);
       psi(i) = psi_new;
    }
    delta = sqrt(psi_n_psi_norm)/psi_norm;
    cout << numit << ".Iteration" << endl;

  }
  psi.save(vfilename,arma::raw_ascii);
}




}
