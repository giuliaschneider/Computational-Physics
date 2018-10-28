/**
  CS-11
  @file     Ising.cpp
  @author   Giulia Schneider
  @date     03.05.2018
  *version  1.0
  @brief    Generates a lattice with randomly occupied and unoccupied sites
            according to the occupation probability p
*/

#include "Ising.hpp"
#include "savedata.h"
#include "squarelattice.hpp"

#include <iostream>
//#include <iomanip>      // std::setw
//#include <stdio.h>
//#include <algorithm>
//#include <cmath>
#include <math.h>

using namespace std;


Ising::Ising(int L, double kbT, double J, int nSweeps):
  L(L), kbT(kbT), J(J), nSweeps(nSweeps){
  N = L*L;
  lat = new squarelattice(L);

  initializeLattice();
  calcEM();
  //save::printLattice(spins, L);
  simulation();
}


Ising::~Ising(){
  delete lat;
}


void Ising::initializeLattice(){
  for (int i=0; i<N; i++){
    int sigma = rand()%2;
    if(sigma == 0){
      lat->setValue(i, -1);
    }
    else {
      lat->setValue(i, 1);
    }
  }
}


int Ising::calcH(int position){
  int* neighboringValues;
  neighboringValues = lat->returnNNeighboringValues(position);
  int h = 0;

  for(int i=0; i<4; i++){
    h += neighboringValues[i];
  }
  return h;
}


void Ising::calcEM(){
  E = 0;
  M = 0;
  for(int i=0; i<N; i++){
    int h = calcH(i);
    int sigma = lat->getValue(i);
    E += -J*sigma*h;
    M += sigma;
  }
}


void Ising::systemSweep(){
  for (int i=0; i<N; i++){
    singleFlip(i);
  }
}


void Ising::singleFlip(int position){
  int sigma = lat->getValue(position);
  int h = calcH(position);
  double dE = 2*J*sigma*h;

  if(dE<0){
    lat->setValue(position, -sigma);
    E += dE;
    M += -2*sigma;
  }
  else{
    double a = double(double(rand())/RAND_MAX);
    double thresh = min(1.0, exp(-dE/(kbT)));
    if(a<thresh){
      lat->setValue(position, -sigma);
      E += dE;
      M += -2*sigma;
    }
  }
}


void Ising::simulation(){

  vecE = new int[nSweeps];
  vecM = new int[nSweeps];

  char header1[1] = {'E'};
  char header2[1] = {'M'};

  double vec_kbT[6] = {.5, 1.0, 1.5, 2.0, 2.269, 3.0};

  for(int k=0; k<6; k++){
    initializeLattice();
    calcEM();
    for(int m=0; m<nSweeps; m++){
      kbT = vec_kbT[k];
      systemSweep();
      vecE[m] = E;
      vecM[m] = M;
    }
    cout << "E, M" << endl;
    sprintf(filename,"results/ising_n%d_%2.4f.txt",L,kbT);
    save_to_text(header1, header2, vecE, vecM, nSweeps, filename);
  }
  delete[] vecE;
  delete[] vecM;
}
