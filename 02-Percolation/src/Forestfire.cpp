/**
  CS-11
  @file     Forestfire.cpp
  @author   Giulia Schneider
  @date     06.10.2018
  *version  1.0
  @brief    Implementation of the burning algorithm
            and evaluation of the results
*/

#include "Forestfire.hpp"
#include "percolationlattice.hpp"
#include "savedata.h"
#include <iostream>
#include <fstream>
#include <stdio.h>


using namespace std;

Forestfire::Forestfire(int L, double p): L(L), p(p){
  Forest = new percolationlattice(L, p);
}


Forestfire::~Forestfire(){
  //cout << "Destructor " << endl;
  delete Forest;
}


void Forestfire::startFire(){
  /**
  * sets the occupied sites in the first row equal to two
  */

  Forest->setLattice(p,1);

  for(int i=0;i<L;i++){
    if(Forest->getValue(i)!=0){
      Forest->setValue(i,2);
    }
  }
  bottom_reached = false;
  burntNeighbor_thisTimeStep = true;
  //cout << "Fire started" << endl;
}


void Forestfire::burnNeighbors(int position, int t){
  /**
  * checks the North, East, South, West neighbors
  * and sets them to t+1 if they're occupied but not buring (marker = 1)
  */

  // neighbors: 0 north, 1 south, 2 east, 3 west
  neighbors = Forest->getNeighbors(position);
  neighboringValues = Forest->getNeighboringValues(position);

  if(neighboringValues[0]==1){
    Forest->setValue(neighbors[0], t+1);
    burntNeighbor = true;
    }

  if(neighboringValues[1]==1){
    Forest->setValue(neighbors[1], t);
    burntNeighbor = true;
  }

  if(neighboringValues[2]==1){
    Forest->setValue(neighbors[2], t);
    burntNeighbor = true;
  }
  if(neighboringValues[3]==1){
    Forest->setValue(neighbors[3], t);
    burntNeighbor = true;
  }
}


void Forestfire::BurningMethod(bool printFigures){
  /**
  * implementation of the Buring Method algorithm
  * @param printFigures: if true, lattice is saved to png
  */
  t = 2;
  startFire();

  if(printFigures){
    sprintf(filename,"results/figures/2_task_t%02d_p%.2f.png",t,p);
    int r[3], g[3], b[3];
    r[0]= 255; g[0]= 255; b[0]= 255; //white
    r[1]=   0; g[1]= 255; b[1]=   0; //green
    r[2]= 255; g[2]= 255; b[2]= 255; //green
    Forest->saveFigure(filename, r, g, b);
  }

  while(burntNeighbor_thisTimeStep){
    burntNeighbor_thisTimeStep = false;
    t++;

    for(int i=0;i<(L*L);i++){
      if(Forest->getValue(i)==t-1){ //Find burning trees
         burnNeighbors(i,t); //Burn neighboring trees
         if(burntNeighbor){
           burntNeighbor_thisTimeStep = true;
           if(i>=(L*(L-1))){bottom_reached = true;}
        }
      }
    }

    if(printFigures){
      sprintf(filename,"results/figures/2_task_t%02d_p%.2f.png",t,p);
      int *r = new int[t+1]();
      int *g = new int[t+1]();
      int *b = new int[t+1]();
      r[0]= 255; g[0]= 255; b[0]= 255; //white
      r[1]=   0; g[1]= 255; b[1]=   0; //green
      for(int i=2; i<t; i++){
        r[i]= 0; g[i]=   0; b[i]=   0; //black
      }
      r[t]= 255; g[t]=   0; b[t]=   0; //red
      Forest->lat->printLattice();
      delete[] r; delete[] g; delete[] b;
    }
    if(bottom_reached){shortest_path = t-1;}
  }
  lifeTime = t;
}


void Forestfire::stats(int n_experiments){
  /**
  * evaluates the probability of finding a spanning cluster,
    the average shortest path and life time
  * @param n_experiments: number of experiments
  */
  avg_spanningCluster = 0.0;
  avg_shortest_path = 0.0;
  avg_lifeTime = 0.0;

  //Parallelize for loop
  #pragma omp parallel for
  for(int i=0; i<n_experiments; i++){
    srand(i);
    BurningMethod(false);
    if(bottom_reached) {
      avg_spanningCluster += 1.0;
      avg_shortest_path += shortest_path;
    }
    avg_lifeTime += lifeTime;
  }

  avg_shortest_path = (double)(avg_shortest_path/avg_spanningCluster);
  avg_spanningCluster = (double)(avg_spanningCluster/n_experiments);
  avg_lifeTime = (double)(avg_lifeTime/n_experiments);
}


void Forestfire::stats_differentProbabilities(int n_experiments){
  /**
  * evaluates the Burning method for differend occupation probabilites p
  * @param n_experiments: number of experiments to be reapeated for statistics
  */

  for(int i=0; i < size_p_array; i++){
    p = double(i/100.0);
    stats(n_experiments);
    vec_p_spanningCluster[i] = avg_spanningCluster;
    vec_p_shortest_path[i] = avg_shortest_path;
    vec_p_lifeTime[i] = avg_lifeTime;
  }
    sprintf(filename,"results/3a_vec_spanningCluster_N%03d.txt",L);
    save_to_text(vec_p_spanningCluster,size_p_array,filename);
    sprintf(filename,"results/3b_vec_shortest_path_N%03d.txt",L);
    save_to_text(vec_p_shortest_path,size_p_array,filename);
    sprintf(filename,"results/3c_vec_lifeTime_N%03d.txt",L);
    save_to_text(vec_p_lifeTime,size_p_array,filename);
}
