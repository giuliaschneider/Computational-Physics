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
#include "savedata.h"
#include <iostream>
//#include <stdio.h>
//#include <algorithm>
//#include <cmath>
#include <math.h>


using namespace std;




Spheres::Spheres(int n, double R): n(n), R(R){
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


int Spheres::calcDistance(int x, int y, int z, int positon){
  double xDist = pow(x-xpositions[positon],2);
  double yDist = pow(y-ypositions[positon],2);
  double zDist = pow(z-zpositions[positon],2);
  double distance = pow(xDist+yDist+zDist,0.5);
  return distance;
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

      // check overlap
      for(int j=0;j<i;j++){
        double distance = calcDistance(x, y, z, j);
        if(distance<(2*R)){
          overlap = true;
        }
      }
    }
    xpositions[i] = x;
    ypositions[i] = y;
    zpositions[i] = z;
  }
}

void Spheres::getDistances(){
  int index = 0;
  for (int i=0; i<n; i++){
    int x = xpositions[i];
    int y = ypositions[i];
    int z = zpositions[i];
    for(int j=i+1;j<n;j++){
      d[index] = calcDistance(x, y, z, j);
      index++;
      if(index > n*(n-1)/2){
        cout << "index greater" << endl;
      }
    }
  }
}

void Spheres::calc_dmean(){
  /**
  * calculates the mean particle distance for the given configuration
  */
  getDistances();
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
