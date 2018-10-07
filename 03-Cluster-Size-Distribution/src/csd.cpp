/**
  CS-11
  @file     csd.cpp
  @author   Giulia Schneider
  @date     15.05.2018
  *version  1.0
  @brief    Generates a lattice with randomly occupied and unoccupied sites
            according to the occupation probability p
*/

#include "percolationlattice.hpp"
#include "savedata.h"
#include <iostream>
#include <iomanip>      // std::setw
#include <stdio.h>


using namespace std;


csd::csd(int N, double p): p(p), L(L){
  lat = new percolationlattice(L, p);
}


csd::~csd(){
  delete lat;
}


void csd::found_newCluster(int &position){
  /**
      @brief: part of the Hoshen- Kopelman algorithm; when a new Cluster is found
      @param position:  current lattice position
      @return void
  */
  kmax++;
  lat[position]=kmax;
  M.push_back(1);
}

void csd::updateM(int k){
  /**
      @brief: part of the Hoshen- Kopelman algorithm; increases M(k)
      @param k:  current k value
      @return void
  */
  while(M[k]<0) {k=-M[k];}
  M[k]++;
  if(M[k]>Mmax){Mmax = M[k];}
}

void csd::set_k(int position){
  /**
  * part of the Hoshen- Kopelman algorithm;
    sets the k value at the current position
  * @param position:  current lattice position
  */
  
  // check if site is occupied
  if(lat->getValue(position)==1){

    // check if site is part of the boundary
    if(position == 0){ // check if site is upper left corner
      lat[position] = kmax; M.push_back(1);
    }
    else if(position < N){ // check if position is part of upper boundary
      // check if left neighbor is unoccupied
      if(lat[position-1]==0){ found_newCluster(position);}
      else{ // left neighbor occupied
        lat[position]=lat[position-1];
        updateM(lat[position-1]);
      }
    }
    else if(position%N==0){ // check if position is part of left boundary

      // check if top neighbor is unoccupied
      if(lat[position-N]==0){ found_newCluster(position);}
      else{ // left neighbor occupied
        lat[position]=lat[position-N];
        updateM(lat[position-N]);
      }
    }

    else{ // site is not on boundary
      if(lat[position-N]==0){ // check if top neighbor is unoccupied
        if(lat[position-1]==0){ // check if left neighbor is unoccupied
          found_newCluster(position);
        }
        else{ // top unoccupied, left occupied
          lat[position] = lat[position-1];
          updateM(lat[position-1]);
        }
      }
      else{// top neighbor occupied
        if(lat[position-1]==0){ // left neighbor unccupied
          lat[position] = lat[position-N];
          updateM(lat[position-N]);
        }
        else{// top and left neighbor occupied
            int k1 = lat[position-N];
            int k2 = lat[position-1];
            while(M[k1]<0) {k1=-M[k1];}
            while(M[k2]<0) {k2=-M[k2];}
          if(k1 == k2){
            lat[position] = k1;
            updateM(k1);
          }
          else{
            lat[position] = k1;
            M[k1] += M[k2] + 1;
            M[k2] =  -k1;
            if(M[k1]>Mmax){Mmax = M[k1];}
          }
        }
      }
    }
  }
}

void csd::countClusters(){
  /**
      @brief: counts the cluster of different sizes
      @return void
  */
  nClusters.assign(Mmax, 0);
  for(int k=2;k<=kmax;k++){
    if(M[k]>0) {nClusters[M[k]-1]++;}
  }
}

void csd::calcCSD(){
  /**
      @brief: calculates the cluster size distribution and saves it to the vector M
  */
  lat->setLattice(p,1);
  kmax = 2;
  M.assign(2,0);
  Mmax = 0;

  for(int i=0;i<(L*L);i++){
    set_k(i);
  }

  countClusters();

}

void csd::calcCSD_different_p(){
  /**
      @brief: calculates the CSD for different p and saves them to a text file
      @return void
  */
  double p_array[10] = {.1,.2,.3,.4,.5,0.592746,.6,.7,.8,.9};
  for(int i = 0;i<10;i++){
    p = p_array[i];
    calc_ClusterSizeDistribution();
    sprintf(filename,"python_scripts/CSD_N%d_p%.2f.txt",N,p);
    save_to_text(&nClusters,filename);
    sprintf(filename,"python_scripts/lat_N%d_p%.2f.ppm",N,p);
    //saveFigure(filename);

  }
  cout << "Fertig" << endl;
}
