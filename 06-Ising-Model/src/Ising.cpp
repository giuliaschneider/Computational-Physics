/**
  CS-11
  @file     Ising.cpp
  @author   Giulia Schneider
  @date     03.11.2018
  *version  1.0
  @brief    Implements the Ising model, each site has value +/- 1
            The system is generated according to M(RT)2-algorithm
            Calculates the energy and magnetization of the system
*/

#include "Ising.hpp"
#include "savedata.h"
#include "squarelattice.hpp"
#include <iostream>
#include <math.h>

using namespace std;


Ising::Ising(int L, double kbT, double J, int nSweeps):
  L(L), kbT(kbT), J(J), nSweeps(nSweeps){
  N = L*L;
  lat = new squarelattice(L);

}


Ising::~Ising(){
  delete lat;
}


void Ising::initializeLattice(){
  /**
  * initalizes all sites to either +1 or -1
  */
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
  /**
  * calculates h as the sum of spins of the nearest neighbors
  * @param position: current lattice position
  * returns h
  */
  int* neighboringValues;
  neighboringValues = lat->returnNPeriodicNeighboringValues(position);
  int h = 0;
  //printVector(neighboringValues, 4);

  for(int i=0; i<4; i++){
    h += neighboringValues[i];
  }
  //cout << "h = " << h << endl;
  return h;
}


void Ising::calcEM(){
  /**
  * calculates the energy and magnetization of the whole system
  */
  E = 0.0;
  M = 0;
  int* neighboringValues;

  for(int i=0; i<N; i++){
    int sigma = lat->getValue(i);
    int h = calcH(i);
    E -= J*sigma*h;
    M += sigma;
  }
}

void Ising::systemSweep(){
  /**
  * performs a system sweep
  */
  for (int i=0; i<N; i++){
    singleFlip(i);
  }
}

void Ising::singleFlip(int position){
  /**
  * perform a single flip at given position
  * @param position: current lattice position
  */
  int sigma = lat->getValue(position);
  int h = calcH(position);
  double dE = 2*J*sigma*h;

  if(dE<=0){
    lat->setValue(position, -sigma);
    E += dE;
    M += -2*sigma;
  }
  else{
    double a = double(double(rand())/RAND_MAX);
    double thresh = min(1.0, exp(-dE/(kbT)));
    if(a<thresh){
      //cout << "dE = " << dE << endl;
      lat->setValue(position, -sigma);
      E += dE;
      M += -2*sigma;
    }
  }
}


void Ising::systemRelaxation(){
  /**
  * calculates the magnetization and energy starting from a disordered state
    saves the energy and magnetization after every system in a text file
  */
  vecE = new double[nSweeps]();
  vecM = new int[nSweeps]();

  char header1[1] = {'E'};
  char header2[1] = {'M'};

  double karr[6] = {0.5, 1, 1.5, 2, 2.2690, 3};

  for(int i=0; i<6; i++){
    kbT = karr[i];
    cout << "kBT = " << kbT << endl;
    initializeLattice();
    calcEM();
      for(int m=0; m<nSweeps; m++){
        systemSweep();
        vecE[m] = E;
        vecM[m] = M;
      }
    sprintf(filename,"results/relaxation_n%d_%2.4f.txt",L,kbT);
    save_to_text(header1, header2, vecE, vecM, nSweeps, filename);
  }
  delete[] vecE;
  delete[] vecM;
}


void Ising::averageM(){
  /**
  * calculates the magnetization and energy starting from a quasi ordered state
    saves the energy and magnetization after every system in a text file
  */
  vecE = new double[nSweeps]();
  vecM = new int[nSweeps]();

  char header1[1] = {'E'};
  char header2[1] = {'M'};

  initializeLattice();
  calcEM();
  for(int i=0; i<1000; i++ ){
    systemSweep();
  }

  for(double k=0.5; k<3.1; k+=0.1){
    kbT = k;
    cout << "kBT = " << kbT << endl;
    for(int m=0; m<nSweeps; m++){
      systemSweep();
      vecE[m] = E;
      vecM[m] = M;
    }
    sprintf(filename,"results/ising_n%d_%2.4f.txt",L,kbT);
    save_to_text(header1, header2, vecE, vecM, nSweeps, filename);
  }
  delete[] vecE;
  delete[] vecM;
}
