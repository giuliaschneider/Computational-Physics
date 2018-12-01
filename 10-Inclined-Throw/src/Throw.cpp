/**
  CS-11
  @file     Throw.cpp
  @author   Giulia Schneider
  @date     24.06.2018
  *version  1.0
  @brief    Wraps up the parameters and right hand side function of the
            inclined throw problem
*/

#include "Throw.hpp"
#include "ODEintegrator.hpp"
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include <functional>

#define PI 3.14159265

using namespace std;


namespace comphys{

Throw::Throw(){
  gair = 0.0;
  v0 = 40.0;
  t0 = 0.0;
  tend = 10;
  n_steps=1000;
  i = 0;
}

arma::vec Throw::F(arma::vec y, double t){
/**
    @brief: right hand side function of the inclined throw problem
    @param y: variables at current time step
    @param t: current time step
    @return arma::vec right hand side function of y' = f(y)
*/
  /*
  y[0]: x
  y[1]: z
  y[2]: vx
  y[3]: vz
  */
  double v = sqrt(pow(y[2],2)+pow(y[3],2));
  arma::vec Ff = {y[2],y[3],-gair*v*y[2],-9.81-gair*v*y[3]};
  return Ff;
}

void Throw::vary_gamma(){
  /**
    @brief: Calculates the trajectory for different alphas and gammas
    @return void
  */
  for(int alpha=5; alpha<90; alpha+=1){
    for(double j=0.0;j<5.5;j+=0.5){
      i++;
      gair = j;
      arma::vec y0 = {0,0,v0*cos(alpha*PI/180.0),v0*sin(alpha*PI/180.0)};
      sprintf(filename,"results/%d_run_alpha_%i_gamma_%.2f.txt",i,alpha,gair);
      auto pF = std::bind(&Throw::F,this,std::placeholders::_1,std::placeholders::_2);
      comphys::rk4 myode(y0,t0,tend,n_steps,pF,filename);
      myode.integrate();
    }
  }
}

}
