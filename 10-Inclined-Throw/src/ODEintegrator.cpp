/**
  CS-11
  @file     ODEintegrator.cpp
  @author   Giulia Schneider
  @date     03.05.2018
  *version  1.0
  @brief    ODEintegrator integrates an autonom first order ODE with n_steps
*/

#include "ODEintegrator.hpp"
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>


using namespace std;



namespace comphys{

ODEintegrator::ODEintegrator(arma::vec y0, double t0, double tend, int n_steps,std::function<arma::vec(arma::vec,double)> pF,const char* vfilename):
y0(y0), t0(t0), tend(tend), n_steps(n_steps), pF(pF), vfilename(vfilename){
  dt = (tend-t0)/n_steps;
  y = y0;
  t = t0;
  d = y0.n_rows;
  output.zeros(d+1, n_steps+1);
}


void ODEintegrator::step(){
/**
    @brief: virtual function, needs subclass to specify
    @return void
*/
}

void ODEintegrator::integrate(){
  /**
      @brief: integration of a first order ODE in n_steps
      @return arma::vec output
        output[0,:]: t
        output[1,:]: x
        output[2,:]: z
        output[3,:]: vx
        output[4,:]: vz
*/
  output(0,0) = t0;
  cout << "d = " << d << endl;
  output.col(0).subvec(1,d) = y0;


  cout << "Integrate " << endl;
  int i = 0;
  for(i=0;i<n_steps;i++){
    cout << "i = " << i << endl;
    step();
    t += dt;
    output(0,i+1) = t;
    output.col(i+1).subvec(1,d) = y;
    if(y(1)<0){break;}
  }

  //cout << output.t() << endl;
  output = output(arma::span(0,d),arma::span(0,i));
  output.save(vfilename,arma::raw_ascii);
}

rk4::rk4(arma::vec y0, double t0, double tend, int n_steps,std::function<arma::vec(arma::vec,double)> pF,const char* vfilename):
  ODEintegrator(y0,t0,tend,n_steps,pF,vfilename){}

void rk4::step(){
  /**
      @brief: performs one rk4 step
      @return void
  */
  arma::vec k1 = pF(y,t);
  arma::vec k2 = pF(y+0.5*dt*k1,t+0.5*dt);
  arma::vec k3 = pF(y+0.5*dt*k2,t+0.5*dt);
  arma::vec k4 = pF(y+dt*k3,t+dt);
  y = y + dt*(k1+2*k2+2*k3+k4)/6.0;
}


}
