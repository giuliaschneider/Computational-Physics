/**
  CS-11
  @file     Spheres.cpp
  @author   Giulia Schneider
  @date     03.05.2018
  *version  1.0
  @brief    Generates a lattice with randomly occupied and unoccupied sites
            according to the occupation probability p
*/

#include "Spheres.hpp"
#include "savedata.hpp"
#include <iostream>
#include <iomanip>      // std::setw
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <math.h>


using namespace std;




Spheres::Spheres(int n,double R): n(n), R(R){
  L = pow(50*n*4/3*M_PI*pow(R,3),1/3);
  cout << L << endl;

  xpositions = new double[n];
  ypositions = new double[n];
  zpositions = new double[n];
  d = new double[n*(n-1)/2];
}

Spheres::Spheres(int n, double R, double L): n(n), R(R),  L(L){
  xpositions = new double[n];
  ypositions = new double[n];
  zpositions = new double[n];
  d = new double[n*(n-1)/2];
}

Spheres::~Spheres(){
  delete[] xpositions;
  delete[] ypositions;
  delete[] zpositions;
  delete[] d;
}


void Spheres::createSpheres(){
  /**
      @brief: creates n spheres randomly in a box which fullfill the no-overlap condition
      @return void
  */

  double x = 0;
  double y = 0;
  double z = 0;
  int index = 0;
  for (int i=0; i<n; i++){
    //cout << i << "te Kugel " << endl;
    bool overlap = true;
    while(overlap){
      overlap = false;
      x = double(rand()*L/RAND_MAX);
      y = double(rand()*L/RAND_MAX);
      z = double(rand()*L/RAND_MAX);
      //cout << x << "; " << y << "; " << z << endl;
      for(int j=0;j<i;j++){
        double distance = pow(pow(x-xpositions[j],2)+pow(y-ypositions[j],2)+pow(z-zpositions[j],2),0.5);
        //cout << "Distanz = " << distance << endl;
        if(distance<(2*R)){
          //cout << " Break " << endl;
          overlap = true;
          break;
        }
        //cout << "Distanz = " << distance << endl;
        d[index] = distance;
        index++;
      }
    }
    xpositions[i] = x;
    ypositions[i] = y;
    zpositions[i] = z;
  }
  //save::printPositions(xpositions, ypositions, zpositions, n);
  //save::printVector(d, n*(n-1)/2);
}

void Spheres::calc_dmean(){
  /**
      @brief: calculated the mean particle distance of the n spheres generated
      @return void
  */
  dmean = 0.0;
  for(int i=0;i<n*(n-1)/2;i++){
    dmean = dmean + d[i];
  }
  dmean = 2*dmean/(n*(n-1));
}

double Spheres::get_dmean(){
  /**
      @brief: returns the mean particle distance
      @return double mean particle distance
  */
  calc_dmean();
  //cout << "dmean = " << dmean << endl;
  return dmean;
}
