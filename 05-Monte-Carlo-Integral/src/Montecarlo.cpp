/**
  CS-11
  @file     Spheres.cpp
  @author   Giulia Schneider
  @date     03.05.2018
  *version  1.0
  @brief    Generates a lattice with randomly occupied and unoccupied sites
            according to the occupation probability p
*/
#include "Montecarlo.cpp"
#include "Spheres.hpp"
#include "savedata.hpp"
#include <iostream>
#include <iomanip>      // std::setw
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <math.h>


using namespace std;


void mc(int M){
  
  int n  = 10;
  int R = 1;
  int L = 20;
  Spheres inbox(n,R,L);

  double I = 0;

  for(int i=0;i<M;i++){
    inbox.createSpheres();
    double dmean = inbox.get_dmean();
    I += dmean;
  }
  I /= M;
  cout << "I = " << I << endl;
}
