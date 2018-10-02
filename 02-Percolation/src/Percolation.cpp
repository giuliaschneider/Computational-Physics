/**
  CS-11
  @file     Percolation.cpp
  @author   Giulia Schneider
  @date     03.05.2018
  *version  1.0
  @brief    Generates a lattice with randomly occupied and unoccupied sites
            according to the occupation probability p
*/

#include "Percolation.hpp"
#include "latticeview.h"
#include <iostream>
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
  Print_lattice (lat, N, N, Percolation::ImageWidth, ImageHeight, filename);
  // In order to save memory you can directly convert the ppm's to any other format like, e.g. png. Use the following code to convert ppm to another format (e.g. png, could be jpg, etc.)
  //char cmd[160],filename_png[160];
  //sprintf(filename_png,"../report/figures/task1_%03f.png",1);
  //sprintf(cmd,"sips -s format png %s --out %s; rm -f %s",filename,filename_png,filename); // rm automatically deletes the ppm-file to save memory (removes test002.ppm)
  //system(cmd);
}

void Percolation::calc_different_p(){
  /**
      @brief: generates lattices for different occupation probabilites
              and saves them as images
      @return void
  */
  double p_array[10] = {.2,.3,.4,.5,.53,.55,.57,.6,.65,.7};
  for(int i = 0;i<10;i++){
    createLattice(p_array[i],1);
    sprintf(filename,"../report/figures/1_task_p%.2f.png",p_array[i]);
    saveFigure(filename);
  }
}
