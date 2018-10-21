/**
  CS-11
  @file     Fractal.cpp
  @author   Giulia Schneider
  @date     21.10.2018
  *version  1.0
  @brief    Generates a lattice with randomly occupied and unoccupied sites
            according to the occupation probability p
*/

#include "Fractal.hpp"
#include "savedata.h"
#include <iostream>
#include <iomanip>      // std::setw
#include <stdio.h>
#include <vector>
#include <math.h>



using namespace std;


Fractal::Fractal(squarelattice* arr): lat(arr){
  cout << "Construction fractal" << endl;
  L = lat->getLatticeSize();

}


Fractal::~Fractal(){
}


int Fractal::findOccupiedCenterPosition(){
  /**
  * Finds a occupied site close to the center of the system
  * @return: position as linear index
  */

  int center = 0;

  if(L%2==1){ // lattice size uneven
    center = floor(L*L/2);
  }
  else{
    center = floor(L*L/2)-L/2;
  }

  // Find occupied center
  if(lat->getValue(center)==1){
    return center;
  }
  else{
    bool found = false;
    int offset = 0;
    int* neighboringPositions;
    int index = 0;

    while(!found){
      neighboringPositions = lat->getNeigboringPositions(center, offset);
      for(int j=0; j<8; j++){
        if(neighboringPositions[j]>0){
          if(lat->getValue(neighboringPositions[j])==1){
            found = true;
            index = j;
            break;
          }
        }
      }
      offset++;
    }
    return neighboringPositions[index];
  }
}


void Fractal::SandBox(){
  /**
  * Calculates the fractal dimension using the sandbox algorithm
  */

  // initialze temporary variables
  vector<int> M;
  vector<int> vecR;

  int center = findOccupiedCenterPosition();
  int shift = 0;
  int position = 0;
  int upperleftcorner = 0;

  // Find maximal Radius centering the occupied center point
  int xCenter = int(center/L);
  int yCenter = center%L;
  int minRx = min(xCenter*2, (L-xCenter-1)*2);
  int minRy = min(yCenter*2, (L-yCenter-1)*2);
  int Rmax = min(minRx, minRy) +1;

  for(int R=3;R<=Rmax;R+=2){
    // calculate the upperleft corner of the sandbox of size R
    shift = (R-1)/2;
    upperleftcorner = center-shift-shift*L;
    // count the occupied sites in the sandbox
    int nCount = 0;
    for(int i=0;i<R*R;i++){
      if(i==0){position = upperleftcorner;}
      else if(i%R==0){position += L-R+1;}
      else {position++;}
      if(lat->getValue(position)==1){nCount++;}
    }
    M.push_back(nCount);
    vecR.push_back(R);
  }

  if(Rmax<L){
    int nCount = 0;
    for(int i=0;i<L*L;i++){
      if(lat->getValue(i)==1){nCount++;}
    }
    M.push_back(nCount);
    vecR.push_back(L);
  }

  sprintf(filename,"results/SandBox_MR_N%d.txt",L);
  save_to_text(vecR, M, filename);

}


void Fractal::BoxCountingMethod(){
  /**
  * Implementation of the Box counting algorithm to calculate the fractal dimension
  */
  // initialze temporary variables
  vector<int> NL;
  NL.assign(L,0);
  int position = 0;


  for(int eps=1;eps<=L;eps++){
    int nBoxes = (1+(L-1)/eps); // round up L/eps

    //loop through all boxes
    for(int i=0;i<nBoxes*nBoxes;i++){
      int gridrow = i/nBoxes*eps;
      int upperleftcorner = gridrow*L+i%nBoxes*eps;

      // uneven size of boxes in lattices
      if((L%eps!=0) and (i%nBoxes*eps>(L/eps)*eps-1) and (i/nBoxes*eps>(L/eps)*eps-1)) {
        // check if box is at lower right corner
        int Lboundary = L%eps;
        for(int j=0;j<Lboundary*Lboundary;j++){
          int cellrow = j/Lboundary;
          position = upperleftcorner +cellrow*L + j%Lboundary;
          //cout << "Position = " << position << endl;
          if(lat->getValue(position)==1){
            NL[eps-1]++;
            break;
          }
        }
      }
      // check if box is on lower boundary
      else if( (L%eps!=0) and (i/nBoxes*eps>(L/eps)*eps-1)){
        //cout << "lower boundary " << endl;
        int Lboundary = L%eps;
        for(int j=0;j<Lboundary*eps;j++){
          int cellrow = j/eps;
          position = upperleftcorner +cellrow*L + j%eps;
          //cout << "Position = " << position << endl;
          if(lat->getValue(position)==1){
            NL[eps-1]++;
            break;
          }
        }
      }
      // check if box in on right boundary
      else if((L%eps!=0) and (i%nBoxes*eps>(L/eps)*eps-1)){
        //cout << "Right boundary " << endl;
        int Lboundary = L%eps;
        for(int j=0;j<Lboundary*eps;j++){
          int cellrow = j/Lboundary;
          position = upperleftcorner +cellrow*L + j%Lboundary;
          //cout << "Position = " << position << endl;
          if(lat->getValue(position)==1){
            NL[eps-1]++;
            break;
          }
        }
      }
      else{
        for(int j=0;j<eps*eps;j++){
          int cellrow = j/eps;
          position = upperleftcorner +cellrow*L + j%eps;
          //cout << "Position = " << position << endl;
          if(lat->getValue(position)==1){
            NL[eps-1]++;
            break;
          }
        }
      }
    }
  }
  sprintf(filename,"results/BoxCounting_NR_N%d.txt",L);
  save_to_text(&NL,filename);
}
