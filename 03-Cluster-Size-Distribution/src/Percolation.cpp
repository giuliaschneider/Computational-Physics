/**
  CS-11
  @file     Percolation.cpp
  @author   Giulia Schneider
  @date     15.05.2018
  *version  1.0
  @brief    Generates a lattice with randomly occupied and unoccupied sites
            according to the occupation probability p
*/

#include "Percolation.hpp"
#include "latticeview.h"
#include "savedata.h"
#include <iostream>
#include <iomanip>      // std::setw
#include <stdio.h>


using namespace std;


Percolation::Percolation(int N): N(N), ImageWidth(1000), ImageHeight(1000){
  lat = new int[N*N] ;
}

Percolation::Percolation(int N, double p): p(p), N(N), ImageWidth(1000), ImageHeight(1000){
  lat = new int[N*N] ;
}

Percolation::~Percolation(){
  delete[] lat;
}


void Percolation::createLattice(double p, int marker){
  /**
      @brief: Generates a lattice with randomly occupied and unoccupied sites
              according to the occupation probability p
      @param p:      occupation probability
      @param marker: marks the occupied sites with markes
      @return void
  */
  srand(time(0));
  for (int icounter=0; icounter<N*N; icounter++){
    z = 1.0*rand()/RAND_MAX;
    if(z<p){
      lat[icounter]= (int)(marker);
    }
    else{
      lat[icounter]= (int)(0);
    }
  }
}

void Percolation::saveFigure(char *filename){
  /**
      @brief: saves the generated laticce to a png-file
      @param filename: name of the generated output file
      @return void
  */
  cout << "Printing " << endl;
  Print_lattice (lat, N, N, ImageWidth, ImageHeight, filename);
  // In order to save memory you can directly convert the ppm's to any other format like, e.g. png. Use the following code to convert ppm to another format (e.g. png, could be jpg, etc.)

}

void Percolation::calc_different_p(){
  /**
      @brief: generates lattices for different occupation probabilites
              and saves them as images
      @return void
  */
  double p_array[10] = {.1,.2,.3,.4,.5,.6,.7,.8,.9,1.0};
  for(int i = 0;i<10;i++){
    createLattice(p_array[i],1);
    sprintf(filename,"../report/figures/1_task_p%.2f.png",p_array[i]);
    saveFigure(filename);
  }
}

void Percolation::found_newCluster(int &position){
  /**
      @brief: part of the Hoshen- Kopelman algorithm; when a new Cluster is found
      @param position:  current lattice position
      @return void
  */
  kmax++;
  lat[position]=kmax;
  M.push_back(1);
}

void Percolation::updateM(int k){
  /**
      @brief: part of the Hoshen- Kopelman algorithm; increases M(k)
      @param k:  current k value
      @return void
  */
  while(M[k]<0) {k=-M[k];}
  M[k]++;
  if(M[k]>Mmax){Mmax = M[k];}
}

void Percolation::set_k(int position){
  /**
      @brief: part of the Hoshen- Kopelman algorithm; sets the k value at the current position
      @param position:  current lattice position
      @return void
  */
  // check if site is occupied
  if(lat[position]==1){

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

void Percolation::printLattice(){
  /**
      @brief: prints the lattice to console
      @return void
  */
  for(int i=0;i<(N*N);i++){
    cout <<  setw(2);
    if(i%N==N-1){
      cout << lat[i] << "|" << endl;
    }
    else{

    cout <<  lat[i] << "|"<< flush;
    }
  }
}

void Percolation::countClusters(){
  /**
      @brief: counts the cluster of different sizes
      @return void
  */
  nClusters.assign(Mmax, 0);
  for(int k=2;k<=kmax;k++){
    if(M[k]>0) {nClusters[M[k]-1]++;}
  }
}

void Percolation::calc_ClusterSizeDistribution(){
  /**
      @brief: calculates the cluster size distribution and saves it to the vector M
      @return void
  */
  createLattice(p,1);
  kmax = 2;
  M.assign(2,0);
  Mmax = 0;

  for(int i=0;i<(N*N);i++){
    set_k(i);
  }

  countClusters();

}

void Percolation::calcCSD_different_p(){
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
