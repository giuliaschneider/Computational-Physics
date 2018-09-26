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

PDEintegrator::PDEintegrator(int N, arma::vec b, double atol, string vfilename):
  N(N), b(b), atol(atol),vfilename(vfilename) {
    dx = 1.0/N;
    n_innergrid = N-2;
    psi.set_size((N-2)*(N-2));
    psi.fill(0.0);
    cout << "Done... " << endl;
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
  while(delta >= atol){
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
  while(delta >= atol){
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
