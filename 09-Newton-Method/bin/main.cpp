#include <iostream>
#include <math.h>
#include <armadillo>
#include "Nullstelle.hpp"


using namespace std;

arma::vec f(arma::vec x){
  double x0 = 5.2;
  double y0 = 2.2;
  arma::vec res(2);
  double exponential = exp(-pow((x(0)-x0),2)-pow((x(1)-y0),2));
  res(0) =  -2*(x(0)-x0)*exponential;
  res(1) =  -2*(x(1)-y0)*exponential;
  return res;
}

arma::mat Df(arma::vec x){
  double x0 = 5.2;
  double y0 = 2.2;
  arma::mat res(2,2);
  double exponential = exp(-pow((x(0)-x0),2)-pow((x(1)-y0),2));
  res(0,0) = exponential*(-2+4*pow((x(0)-x0),2));
  res(1,0) = 4*(x(1)-y0)*(x(0)-x0)*exponential;
  res(0,1) = 4*(x(1)-y0)*(x(0)-x0)*exponential;
  res(1,1) = exponential*(-2+4*pow((x(1)-y0),2));
  return res;
}



int main(){

  /*
  Task 1
  */
  arma::vec xstar;
  xstar << 5.2 << 2.2 << arma::endr;
  arma::vec x0;
  char filename[160];

  double i = 4.8;
  while(i<5.6){
    x0 << i << i-3 << arma::endr;
    sprintf(filename,"results/newton_error_x0_%.2f.txt",i);
    comphys::printErrorNewton(xstar,2,x0,f,Df,filename);
    sprintf(filename,"results/Secant_error_x0_%.2f.txt",i);
    //comphys::printErrorSecant(xstar,2,x0,f,filename);
    i+=0.05;
  }






  return 0;
}
