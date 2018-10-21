/**
  CS-11
  @file     Spheres.cpp
  @author   Giulia Schneider
  @date     21.10.2018
  *version  1.0
  @brief    Generates n non-overelapping spheres with radius R
            randomly distributed within a cube of volume LxLxL
*/

#include "Spheres.hpp"
#include "savedata.hpp"
#include <iostream>
//#include <stdio.h>
//#include <algorithm>
//#include <cmath>
#include <math.h>


using namespace std;




Spheres::Spheres(int n,double R): n(n), R(R){
  L = pow(50*n*4/3*M_PI*pow(R,3),1/3);
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
  * Generates n non-overlapping spheres with radius R
  */

  // Initialize variables
  double x = 0;
  double y = 0;
  double z = 0;
  int index = 0;

  // Generate spheres
  for (int i=0; i<n; i++){
    bool overlap = true;

    // draw new position
    while(overlap){
      overlap = false;
      x = double(rand()*L/RAND_MAX);
      y = double(rand()*L/RAND_MAX);
      z = double(rand()*L/RAND_MAX);
      //cout << x << "; " << y << "; " << z << endl;

      // check overlap
      for(int j=0;j<i;j++){
        double xDist = pow(x-xpositions[j],2)
        double yDist = pow(y-ypositions[j],2)
        double zDist = pow(z-zpositions[j],2)
        double distance = pow(xDist+yDist+zDist,0.5);
        if(distance<(2*R)){
          overlap = true;
        }
        else{
          d[index] = distance;
          index++;
        }
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
  * calculates the mean particle distance for the given configuration
  */
  dmean = 0.0;

  // iterate through all particle-particle distances
  for(int i=0;i<n*(n-1)/2;i++){
    dmean += d[i];
  }
  dmean = 2*dmean/(n*(n-1));
}

double Spheres::get_dmean(){
  /**
  * returns the mean particle distance for the given configuration
  */
  calc_dmean();
  return dmean;
}
