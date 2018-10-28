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
#include "savedata.hpp"
#include <iostream>
#include <iomanip>      // std::setw
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <math.h>


using namespace std;


Ising::Ising(int L, double kbT, double J, int nSweeps):
L(L), kbT(kbT), J(J), nSweeps(nSweeps){
  N = L*L;
  J = 1.0;
  spins = new int[N];
  initializeLattice();
  calcEM();
  //save::printLattice(spins, L);
  simulation();
}


Ising::~Ising(){
  delete[] spins;
}


void Ising::initializeLattice(){
  for (int i=0; i<N; i++){
    int sigma = rand()%2;
    if(sigma == 0){
      spins[i] = -1;
    }
    else {
      spins[i] = 1;
    }
  }
}


void Ising::getNeighbors(int position){
  if(position < L){ // upper boundary
    north = (L*(L-1)) + position;
    south = position+L;
  }
  else if(position >= (L*(L-1))){ //lower boundary
    north = position-L;
    south = position%L;
  }
  else { // not on boundary
    north = position-L;
    south = position+L;
  }

  if(position%L == 0){ // eastern boundary
    east = position + (L-1);
    west = position+1;
  }
  else if(position%L == (L-1)){ //western boundary
    east = position-1;
    west = position - (L-1);
  }
  else { // not on boundary
    east = position-1;
    west = position+1;
  }
}

void Ising::calcEM(){
  E = 0;
  M = 0;
  for (int i=0; i<N; i++){
    getNeighbors(i);
    E += -J*spins[i]*(spins[north]+spins[south]+spins[east]+spins[west]);
    M += spins[i];
  }
}


void Ising::systemSweep(){
  for (int i=0; i<N; i++){
    singleFlip(i);
  }
}


void Ising::singleFlip(int position){
  getNeighbors(position);
  int sigma = spins[position];
  int h = spins[north]+spins[south]+spins[east]+spins[west];
  double dE = 2*J*sigma*h;

  if(dE<0){
    spins[position] = -spins[position];
    E += dE;
    M += -2*spins[position];
  }
  else{
    double a = double(double(rand())/RAND_MAX);
    double thresh = min(1.0, exp(-dE/(kbT)));
    if(a<thresh){
      spins[position] = -spins[position];
      E += dE;
      M += -2*spins[position];
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
    sprintf(filename,"python_scripts/n%d/ising_n%d_%2.4f.txt",L,L,kbT);
    save::save_to_text(header1, header2, vecE, vecM, nSweeps, filename);

  }




  delete[] vecE;
  delete[] vecM;

}
