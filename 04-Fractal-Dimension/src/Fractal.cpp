/**
  CS-11
  @file     Fractal.cpp
  @author   Giulia Schneider
  @date     03.05.2018
  *version  1.0
  @brief    Generates a lattice with randomly occupied and unoccupied sites
            according to the occupation probability p
*/

#include "Fractal.hpp"
#include "savedata.hpp"
#include <iostream>
#include <iomanip>      // std::setw
#include <stdio.h>
#include <vector>



using namespace std;


Fractal::Fractal(int N): N(N), ImageWidth(1000), ImageHeight(1000){
}


Fractal::~Fractal(){
}

void Fractal::setLattice(int* arr){
  /**
      @brief: set the lattice for which the fractal dimension is to be calculated
      @param arr: lattice
      @return void
  */
  lat = arr;
  cout << "Lattice is set" << endl;
  //save::printLattice(lat,N);
}

void Fractal::SandBox(){
  /**
      @brief: Implementation of the Sandbox algorithm to calculate the fractal dimension
      @return void
  */

  // initialze temporary variables
  vector<int> M;
  M.assign(N-2,0);
  int shift = 0;
  int midpoint = 0;


  if(N%2==1){midpoint = (N*N-1)/2;}
  else {midpoint = (N*N-1)/2-N/2;}
  //cout << midpoint << endl;
  int position = 0;
  int upperleftcorner = 0;

  for(int R=3;R<N+1;R++){
    //cout << "R = " << R << endl;
    // calculate the upperleft corner of the sandbox of size R
    shift = (R-1)/2;
    upperleftcorner = midpoint-shift-shift*N;
    // count the occupied sites in the sandbox
    for(int i=0;i<R*R;i++){
      if(i==0){position = upperleftcorner;}
      else if(i%R==0){position += N-R+1;}
      else {position++;}
      //cout << "Position = " << position << endl;
      if(lat[position]==1){M[R-3]++;}
    }
    //cout << "M(r) = " << M[R-3] << endl;
  }
  sprintf(filename,"python_scripts/SandBox_MR_N%d.txt",N);
  save::save_to_text(&M,filename);
  cout << "Fertig Sandbox" << endl;

}


void Fractal::BoxCountingMethod(){
  /**
      @brief: Implementation of the Box counting algorithm to calculate the fractal dimension
      @return void
  */
  // initialze temporary variables
  vector<int> NL;
  NL.assign(N,0);
  int position = 0;


  for(int L=1;L<N+1;L++){
    //cout << "L = " << L << endl;
    int nBoxes = (1+(N-1)/L); // round up N/L
    //  cout << "nBoxes = " << nBoxes << endl;

    //loop through all boxes
    for(int i=0;i<nBoxes*nBoxes;i++){
      //cout << " Box Nr " << i << endl;
      int gridrow = i/nBoxes*L;
      int upperleftcorner = gridrow*N+i%nBoxes*L;

      if((N%L!=0) and (i%nBoxes*L>(N/L)*L-1) and (i/nBoxes*L>(N/L)*L-1)) { // uneven size of boxes in lattices
        // check if box is at lower right corner
        int Lboundary = N%L;
        for(int j=0;j<Lboundary*Lboundary;j++){
          int cellrow = j/Lboundary;
          position = upperleftcorner +cellrow*N + j%Lboundary;
          //cout << "Position = " << position << endl;
          if(lat[position]==1){
            NL[L-1]++;
            break;
          }
        }
      }
      // check if box is on lower boundary
      else if( (N%L!=0) and (i/nBoxes*L>(N/L)*L-1)){
        //cout << "lower boundary " << endl;

        int Lboundary = N%L;
        for(int j=0;j<Lboundary*L;j++){
          int cellrow = j/L;
          position = upperleftcorner +cellrow*N + j%L;
          //cout << "Position = " << position << endl;
          if(lat[position]==1){
            NL[L-1]++;
            break;
          }
        }
      }
      // check if box in on right boundary
      else if((N%L!=0) and (i%nBoxes*L>(N/L)*L-1)){
        //cout << "Right boundary " << endl;
        int Lboundary = N%L;
        for(int j=0;j<Lboundary*L;j++){
          int cellrow = j/Lboundary;
          position = upperleftcorner +cellrow*N + j%Lboundary;
          //cout << "Position = " << position << endl;
          if(lat[position]==1){
            NL[L-1]++;
            break;
          }
        }
      }
      else{
        for(int j=0;j<L*L;j++){
          int cellrow = j/L;
          position = upperleftcorner +cellrow*N + j%L;
          //cout << "Position = " << position << endl;
          if(lat[position]==1){
            NL[L-1]++;
            break;
          }
        }
      }
    }
  }
  sprintf(filename,"python_scripts/BoxCounting_NR_N%d.txt",N);
  save::save_to_text(&NL,filename);
  cout << "Fertig BoxCounting" << endl;

}
