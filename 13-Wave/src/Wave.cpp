/**
  CS-11
  @file     Wave.cpp
  @author   Giulia Schneider
  @date     26.06.2018
  *version  1.0
  @brief    Generates x0
*/

#include "Wave.hpp"
#include "savedata.h"
#include <iostream>
#include <math.h>

using namespace std;



namespace comphys{

Wave::Wave(double x0, double xend, int h, double t0, double tend, double dt, double c):
  x0(x0), xend(xend), h(h), t0(t0), tend(tend), dt(dt), c(c){
    cout << "Construct... " << endl;

    dx = (xend-x0)/h;
    b = pow(c*dt/dx,2);

    c2 = c/2;
    c1 = c;

    nSteps = int((tend-t0)/dt);
    u_tt = new double[h+1];
    u_now = new double[h+1];
    temp = new double[h+1];

    setIC();

    cout << "b = " << b << endl;
    cout << "h = " << h << endl;
    cout << "nSteps = " << nSteps << endl;

    calcWave();

    cout << "Done... " << endl;
  }


Wave::~Wave(){
  delete[] u_tt;
  delete[] u_now;
  delete[] temp;
}


void Wave::setIC(){
  /**
  Sets the initial condition as the superposition of two waves.
  Return void
  */
  for(int i=0; i<h+1; i++){
    xi = i*dx;
    u_now[i] = exp(-pow((xi-5),2)) + exp(-pow((xi-15),2))  ;
    u_tt[i] = exp(-pow(xi+c1*dt-5,2)) + exp(-pow(xi+c2*dt-15,2));
  }
}


void Wave::calcWave(){
  /**
  Calculates the wave propagation in a explicit finite difference scheme
  Return void
  */
  for(int t=0; t<nSteps+1; t++){
    for(int i=0; i<h+1; i++){
      if(i==0){
        temp[i] = 2.0*(1-b)*u_now[i] + b*(u_now[h]+u_now[i+1]) - u_tt[i];
      }
      else if (i==h){
        temp[i] = 2.0*(1-b)*u_now[i] + b*(u_now[i-1]+u_now[0]) - u_tt[i];
      }
      else{
        temp[i] = 2.0*(1-b)*u_now[i] + b*(u_now[i-1]+u_now[i+1]) - u_tt[i];
      }
    }

    for(int i=0; i<h+1; i++){
      u_tt[i] = u_now[i];
      u_now[i] = temp[i];
    }

    if((tend-t0)/nSteps*t == static_cast<int>((tend-t0)/nSteps*t) ){
      cout << "Saving " << (tend-t0)/nSteps*t << endl;
      sprintf(filename,"results/u_paket_b_%d_t%d.txt", int(100*b), int((tend-t0)/nSteps*t));
      //save::printVector(u_now, h);(tend-t0)/nSteps*t

      save_to_text(temp, h, filename);

    }
  }
}




}
