/**
  CS-11
  @file     PDEintegrator.cpp
  @author   Giulia Schneider
  @date     07.12.2018
  *version  1.0
  @brief    PDEintegrator integrates an elliptic PDE up to tolerance atol
*/

#include "PDEintegrator.hpp"
#include <iostream>


using namespace std;



PDEintegrator::PDEintegrator(int N, arma::vec b, double atol, string vfilename):
  N(N), b(b), atol(atol),vfilename(vfilename) {
    dx = 1.0/N;
    n_innergrid = N-2;
    psi.set_size( n_innergrid*n_innergrid );
    psi.fill(0.0);
  }


void PDEintegrator::integrate(){
  /**
  * Integrates an elliptic PDE up to tolerance atol and save results to text
  */
  delta = 100.0;
  int numit = 0;
  while(delta >= atol){
    numit++;
    step();
  }
  cout << "Done after "<< numit << "iterations" << endl;
  psi.save(vfilename,arma::raw_ascii);
}

void PDEintegrator::step(){
/**
    @brief: virtual function, needs subclass to specify
    @return void
*/
}


RelaxationMethods::RelaxationMethods(int N, arma::vec b, double atol, string vfilename):
  PDEintegrator(N, b, atol, vfilename){}

void RelaxationMethods::step(){
  /**
  * Virtual function, needs subclass to specify
  * Return void
  */
  }

double RelaxationMethods::update_psi(int position){
  /**
  * Calculates the the new value psi at position
  * Return new psi
  */

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

Jacobi::Jacobi(int N, arma::vec b, double atol, string vfilename):
  RelaxationMethods(N, b, atol, vfilename){
    psi_new.set_size((N-2)*(N-2));
    psi_new.fill(0.0);
  }

void Jacobi::step(){
  /**
  Performs one Jacobi relaxation step
  Return void
  */
  for(int i=0;i<(N-2)*(N-2);i++){
    psi_new(i) = update_psi(i);
  }
  delta = arma::norm(psi_new-psi)/arma::norm(psi);
  psi = psi_new;
}


GaussSeidel::GaussSeidel(int N, arma::vec b, double atol, string vfilename):
  RelaxationMethods(N, b, atol, vfilename){}

void GaussSeidel::step(){
  /**
  Performs one Gauss Seidel relaxation step
  Return void
  */
  double psi_norm = arma::norm(psi);
  double psi_new_norm = 0.0;
  double psi_new;
  for(int i=0;i<(N-2)*(N-2);i++){
    psi_new = update_psi(i);
    psi_new_norm += pow(psi_new-psi(i),2);
    psi(i) = psi_new;
  }
  delta = sqrt(psi_new_norm)/psi_norm;
}
