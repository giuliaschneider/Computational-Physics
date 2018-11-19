/**
  CS-11
  @file     Nullstelle.cpp
  @author   Giulia Schneider
  @date     26.06.2018
  *version  1.0
  @brief    Implementation of Newton's method and secant method to calculate the root of a function
*/

#include "Nullstelle.hpp"
#include "savedata.h"
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>


using namespace std;



namespace comphys{


arma::vec Newton(int d, arma::vec x0, arma::vec (*F)(arma::vec), arma::mat (*DF)(arma::vec), double rtol, int maxiter){
  /**
    @brief: calculates the root of the function F using Newton's method
    @param d: dimension of vector x0
    @param x0: arma::vec inital value
    @param F(x): function
    @param DF(x): Jacobi matrix
    @param rtol: relative error tolerance (default rtol = 1*10^-10)
    @param maxiter: maximum number of iterations (default maxiter = 200)
    @return arma::vec root x if converged, otherwise zero
*/
  cout << "Newton " << endl;
  arma::vec x = x0;
  arma::vec s(d);
  int i = 0;
  while((i==0) or ((norm(s)>rtol*norm(x)) and (i<maxiter)) ){
      i++;
      arma::vec Fx = F(x);
      arma::mat DFx = DF(x);
      s = solve(DFx,Fx);
      x = x-s;
  }
  if(i<maxiter){
    return x;
  }
  else{
    return 0*x;
  }
}

void printErrorNewton(arma::vec xstar, int d, arma::vec x0, arma::vec (*F)(arma::vec), arma::mat (*DF)(arma::vec),const char* vfilename,double rtol, int maxiter){
  /**
    @brief: calculates the root of the function F using Newton's method and saves the error at each iteration step to a text file
    @param d: dimension of vector x0
    @param x0: arma::vec inital value
    @param F(x): function
    @param DF(x): Jacobi matrix
    @param vfilename: filename
    @param rtol: relative error tolerance (default rtol = 1*10^-10)
    @param maxiter: maximum number of iterations (default maxiter = 200)
    @return arma::vec root x if converged, otherwise zero
*/
  // initialize variables
  arma::vec x = x0;
  int i = 0;
  vector<double> err;
  vector<int> indexes;
  arma::vec s(d);
  err.push_back(norm(x-xstar)) ;
  indexes.push_back(i);
  while((i==0) or ((norm(s)>rtol*norm(x)) and (i<maxiter)) ){
      arma::vec Fx = F(x);
      arma::mat DFx = DF(x);
      s = solve(DFx,Fx);
      x = x-s;
      i++;
      err.push_back(norm(s));
      indexes.push_back(i);
  }
  int *data1 = &indexes[0];
  double *data2 = &err[0];
  save_to_text(data1,data2,i,vfilename);
  cout << "x0 = " << x0 << endl;
  cout << "xsol = " << x << endl;
}


arma::mat numericalGrad(int d,  arma::vec x0, arma::vec (*F)(arma::vec), double eps){
  /**
    @brief: calculates the numerical gradient of the function F at x:
    @param d: dimension of vector x0
    @param x0: arma::vec inital value
    @param F(x): function
    @param eps: precision parameter (default eps = 10^-16)
    @return arma::mat Jacobi matrix J
*/
  arma::mat grad(d,d);
  for(int i=0;i<d;i++){
      arma::vec x = x0;
      double hj = x0(i)*sqrt(eps);
      x(i) += hj;
      grad.col(i) = (F(x)-F(x0))/hj;
    }
  return grad;
}

arma::vec Secant(int d, arma::vec x0, arma::vec (*F)(arma::vec), double eps,double rtol, int maxiter){
  /**
    @brief: calculates the root of the function F using the secant method
    @param d: dimension of vector x0
    @param x0: arma::vec inital value
    @param F(x): function
    @param eps: precision parameter for calculating the numerical gradient (default eps = 10^-16)
    @param rtol: relative error tolerance (default rtol = 1*10^-10)
    @param maxiter: maximum number of iterations (default maxiter = 200)
    @return arma::vec root x if converged, otherwise zero
*/
  cout << "Secant " << endl;
  arma::vec x = x0;
  arma::vec s(d);
  int i = 0;
  while((i==0) or ((norm(s)>rtol*norm(x)) and (i<maxiter)) ){
      i++;
      arma::vec Fx = F(x);
      arma::mat DFx = comphys::numericalGrad(d,x,F);
      s = solve(DFx,Fx);
      x = x-s;
  }
  return x;
}

void printErrorSecant(arma::vec xstar, int d, arma::vec x0, arma::vec (*F)(arma::vec),const char* vfilename,double rtol, int maxiter){
  /**
    @brief: calculates the root of the function F using the secant method and saves the error at each iteration step to a text file
    @param d: dimension of vector x0
    @param x0: arma::vec inital value
    @param F(x): function
    @param vfilename: filename
    @param rtol: relative error tolerance (default rtol = 1*10^-10)
    @param maxiter: maximum number of iterations (default maxiter = 200)
    @return arma::vec root x if converged, otherwise zero
*/
  arma::vec x = x0;
  int i = 0;
  vector<double> err;
  err.push_back(norm(x-xstar)) ;
  vector<int> indexes;
  indexes.push_back(i);
  arma::vec s(d);
  while((i==0) or ((norm(s)>rtol*norm(x)) and (i<maxiter)) ){
      arma::vec Fx = F(x);
      arma::mat DFx = comphys::numericalGrad(d,x,F);
      s = solve(DFx,Fx);
      x = x-s;
      i++;
      err.push_back(norm(s));
      indexes.push_back(i);
  }
  int *data1 = &indexes[0];
  double *data2 = &err[0];
  save_to_text(data1,data2,i,vfilename);
}

}
