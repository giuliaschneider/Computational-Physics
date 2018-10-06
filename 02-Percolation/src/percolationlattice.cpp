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
}

percolationlattice::percolationlattice(int L, double p): L(L), p(p){
  cout << "Construction percolationlattice" << endl;
  N = L*L;
  lat = new squarelattice(L) ;

}

percolationlattice::~percolationlattice(){
  delete lat;
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
  }
  cout << "Lattice is set " << endl;
}


void percolationlattice::saveFigure(char *filename){
/**
* saves the generated laticce to a png-file
* @param filename: name of the generated output file
*/
  cout << "Saving " << endl;
  lat->saveToPng(filename);
}


void percolationlattice::calc_different_p(){
  /**
      @brief: generates lattices for different occupation probabilites
              and saves them as images
      @return void
  */
  double p_array[10] = {.2,.3,.4,.5,.53,.55,.57,.6,.65,.7};
  for(int i = 0;i<10;i++){
    setLattice(p_array[i],1);
    sprintf(filename,"../report/figures/1_task_p%.2f.png",p_array[i]);
    saveFigure(filename);
  }
}
