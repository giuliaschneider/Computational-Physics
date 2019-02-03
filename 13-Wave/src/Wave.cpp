/**
  CS-11
  @file     Wave.cpp
  @author   Giulia Schneider
  @date     26.06.2018
  *version  1.0
  @brief    Generates x0
*/

#include "Wave.hpp"
#include "savedata.hpp"
#include <iostream>
#include <sstream>
#include <math.h>
#include <cmath>
#include <vector>
#include <armadillo>


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

    cout << "u_tt " << &u_tt << endl;
    cout << "u_now " << &u_now << endl;
    cout << "temp " << &temp << endl;

    //x = arma::linspace(x0,xend,h+1);
    //A = arma::mat(h+1, h+1, arma::fill::zeros);

    setIC();
    //setA();

    //cout << "Unow = " << arma::size(u_now) << endl;
    //cout << "A = " << arma::size(A) << endl;
    //cout << A*u_now << endl;

    cout << "b = " << b << endl;
    cout << "h = " << h << endl;
    cout << "nSteps = " << nSteps << endl;

    calcWave();



    cout << "Done... " << endl;
  }


Wave::~Wave(){
  cout << "u_tt " << &u_tt << endl;
  cout << "u_now " << &u_now << endl;
  cout << "temp " << &temp << endl;

  delete[] u_tt;
  delete[] u_now;
  delete[] temp;
  //delete[] pOriginal;

}

void Wave::setIC(){
  //u_now = exp(-pow((x-10),2));
  //u_tt = exp(-pow(x-c*dt-10,2));



  for(int i=0; i<h+1; i++){
    xi = i*dx;
    //u_now[i] = exp(-pow((xi-10),2));
    //u_tt[i] = exp(-pow(xi-c*dt-10,2));
    //u_now[i] = sin(2*xi/M_PI);
    //u_tt[i] = sin(2*xi/M_PI-c*dt);
    u_now[i] = exp(-pow((xi-5),2)) + exp(-pow((xi-15),2))  ;
    u_tt[i] = exp(-pow(xi+c1*dt-5,2)) + exp(-pow(xi+c2*dt-15,2));
  }

  //save::printVector(u_now, h);

  //cout << x << endl;
  //cout << u_now << endl;
  //cout << u_tt << endl;
}

void Wave::setA(){

  A.diag().fill(2*(1-b));
  A.diag(-1).fill(b);
  A.diag(1).fill(b);
  A.row(0).tail(1) = b;
  A.col(0).tail(1) = b;
  //cout << A << endl;
}


void Wave::calcWave(){
  for(int t=0; t<nSteps+1; t++){
    //u_next = A*u_now - (u_tt);
    //u_tt = u_now;
    //u_now = u_next


    //cout << "t = " << t << endl;

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
      //cout << "next = " << next << endl;
    }


    for(int i=0; i<h+1; i++){
      u_tt[i] = u_now[i];
      u_now[i] = temp[i];
    }
    //u_tt = u_now;
    //u_now = temp;



    if((tend-t0)/nSteps*t == static_cast<int>((tend-t0)/nSteps*t) ){
      cout << "Saving " << (tend-t0)/nSteps*t << endl;
      sprintf(filename,"python_scripts/u_paket_b_%d_t%d.txt", int(100*b), int((tend-t0)/nSteps*t));
      //save::printVector(u_now, h);(tend-t0)/nSteps*t

      save::save_to_text(temp, h, filename);

    }


  }
}




}
