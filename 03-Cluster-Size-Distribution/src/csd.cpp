/**
  CS-11
  @file     csd.cpp
  @author   Giulia Schneider
  @date     13.10.2018
  *version  1.0
  @brief    Calculates the cluster size distribution of a given
            percolation lattice
*/

#include "csd.hpp"
#include "percolationlattice.hpp"

#include "savedata.h"
#include <iostream>
#include <iomanip>      // std::setw
#include <stdio.h>


using namespace std;


csd::csd(int L, double p): L(L), p(p){
  lat = new percolationlattice(L, p);
}

csd::~csd(){
  delete lat;
}


void csd::found_newCluster(int position){
  /**
  * Updates the vector M and increases k
    part of the Hoshen- Kopelman algorithm
  * @param position:  current lattice position
  */
  kmax++;
  lat->setValue(position, kmax);
  M.push_back(1);
}


void csd::updateM(int k){
  /**
  * part of the Hoshen- Kopelman algorithm; increases M(k)
  * @param k:  current k value
  */
  while(M[k]<0) {k=-M[k];}
  M[k]++;
  if(M[k]>Mmax){Mmax = M[k];}
}


void csd::set_k(int position){
  /**
  * sets the k value at the current position
    part of the Hoshen- Kopelman algorithm;
  * @param position:  current lattice position
  */

  // check if site is occupied
  if(lat->getValue(position)==1){

    // save the value at the norther and eastern position
    // if east or north is outside the grid, the value is set to zero
    eastValue = lat->getEasternValue(position);
    northValue = lat->getNorthernValue(position);

    if(northValue==0){//no northern neighbor or north unoccupied
      if(eastValue==0){found_newCluster(position);}
      else{//east occupied
        lat->setValue(position, eastValue);
        updateM(eastValue);
      }
    }
    else{//north occupied
      if(eastValue==0){//no eastern neighbor or east unoccupied
        lat->setValue(position, northValue);
        updateM(northValue);
      }
      else{// top and east neighbor occupied
        int k1 = northValue;
        int k2 = eastValue;
        while(M[k1]<0) {k1=-M[k1];}
        while(M[k2]<0) {k2=-M[k2];}
        if(k1 == k2){
          lat->setValue(position, k1);
          updateM(k1);
        }
        else{
          lat->setValue(position, k1);
          M[k1] += M[k2] + 1;
          M[k2] =  -k1;
          if(M[k1]>Mmax){Mmax = M[k1];}
        }
      }
    }
  }
}


void csd::countClusters(){
  /**
  * counts all clusters
  */
  nClusters.assign(Mmax, 0);
  for(int k=2;k<=kmax;k++){
    if(M[k]>0) {nClusters[M[k]-1]++;}
  }
}

void csd::calcCSD(){
  /**
  * calculates the cluster size distribution and saves it to the vector M
  */

  cout << "Calculalting CSD " << endl;
  lat->setLattice(p,1);
  kmax = 1;
  M.assign(2,0);
  Mmax = 0;

  for(int i=0;i<(L*L);i++){
    set_k(i);
  }

  countClusters();
}


void csd::calcCSD_different_p(){
  /**
  * calculates the CSD for different p and saves them to a text file
  */
  double p_array[10] = {.1,.2,.3,.4,.5,0.592746,.6,.7,.8,.9};

  for(int i = 0;i<10;i++){
    p = p_array[i];
    calcCSD();

    sprintf(filename,"python_scripts/CSD_N%d_p%.2f.txt",L,p);
    save_to_text(&nClusters, filename);
  }
}
