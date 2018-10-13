/**
  CS-11
  @file     percolationlattice.cpp
  @author   Giulia Schneider
  @date     06.10.2018
  *version  1.0
  @brief    Generates a lattice with randomly occupied and unoccupied sites
            according to the occupation probability p
*/

#include "percolationlattice.hpp"
#include "squarelattice.hpp"
#include <iostream>
#include <stdio.h>


using namespace std;


percolationlattice::percolationlattice(int L): L(L){
  N = L*L;
  lat = new squarelattice(L) ;
  p = 0.5;
}

percolationlattice::percolationlattice(int L, double p): L(L), p(p){
  cout << "Construction percolationlattice" << endl;
  N = L*L;
  lat = new squarelattice(L) ;

}

percolationlattice::~percolationlattice(){
  delete lat;
}


void percolationlattice::setValue(int position, int value){
  lat->setValue(position, value);
}

int percolationlattice::getValue(int position){
  return lat->getValue(position);
}


int* percolationlattice::getNeighbors(int position){
  /**
  * Returns an array of the indices of neighbors
  */
  lat->getNeighbors(position);
  neighbors[0] = lat->north;
  neighbors[1] = lat->south;
  neighbors[2] = lat->east;
  neighbors[3] = lat->west;
  return neighbors;
}

int* percolationlattice::getNeighboringValues(int position){
  /**
  * Returns an array of the neighboring values
  */
  lat->getNeighboringValues(position);
  return lat->neighboringValues;
}


int percolationlattice::getNorthernValue(int position){
  return lat->getNorthernValue(position);
}

int percolationlattice::getEasternValue(int position){
  return lat->getEasternValue(position);
}

void percolationlattice::setLattice(double p, int marker){
  /**
  * Generates a lattice with randomly occupied and unoccupied sites
      according to the occupation probability p
  * @param p:      occupation probability
  * @param marker: occupied site is set to marker
  */

  for (int i=0; i<N; i++){
    z = 1.0*rand()/RAND_MAX;
    if(z<p){
      lat->setValue(i, marker);
    }
    else{
      lat->setValue(i, 0);
    }
  }
  //cout << "Lattice is set " << endl;
}


void percolationlattice::saveFigure(char *filename, int* r, int* g, int* b){
/**
* saves the generated laticce to a png-file
* @param filename: name of the generated output file
*/
  cout << "Saving " << endl;
  lat->saveToPng(filename, r, g, b);
}


void percolationlattice::setLattice_differentProbabilities(){
  /**
  * generates lattices for different occupation probabilites
    and saves them as images
  */
  double p_array[10] = {.2,.3,.4,.5,.53,.55,.57,.6,.65,.7};
  for(int i = 0;i<10;i++){
    setLattice(p_array[i],1);
    sprintf(filename,"results/figures/1_task_p%.2f.png",p_array[i]);

    int r[2], g[2], b[2];
    r[0]= 255; g[0]= 255; b[0]= 255; //white
    r[1]=   0; g[1]= 255; b[1]=   0; //green
    saveFigure(filename, r, g, b);
  }
}
