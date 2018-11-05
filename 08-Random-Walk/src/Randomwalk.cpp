/**
  CS-11
  @file     Randomwalk.cpp
  @author   Giulia Schneider
  @date     03.05.2018
  *version  1.0
  @brief    Generates a lattice with randomly occupied and unoccupied sites
            according to the occupation probability p
*/

#include "Randomwalk.hpp"
#include "savedata.hpp"
#include <iostream>
#include <iomanip>      // std::setw
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <math.h>


using namespace std;


Randomwalk::Randomwalk(int nSteps, int M, bool d2, bool saw):
nSteps(nSteps), M(M), d2(d2), saw(saw){
  if(saw){
    positions = new Coordinates[nSteps+1];
  }

  setStartingPosition();

  varyN();
  //varyM();

}


Randomwalk::~Randomwalk(){
  if(saw){
    delete[] positions;
  }
}


void Randomwalk::setStartingPosition(){
  startingPosition.x = 0;
  startingPosition.y = 0;
  startingPosition.z = 0;
}


void Randomwalk::initializeParticle(){
  currentPosition.x = startingPosition.x;
  currentPosition.y = startingPosition.y;
  currentPosition.z = startingPosition.z;
}


void Randomwalk::randomStep(){

  if(d2){
    double theta = (2 * M_PI * rand()) / RAND_MAX;
    currentPosition.x = currentPosition.x + stepSize*cos(theta);
    currentPosition.y = currentPosition.y + stepSize*sin(theta);
    currentPosition.z = currentPosition.z;
  }
  else{
    double theta = (2 * M_PI * rand()) / RAND_MAX;
    double phi = (M_PI * rand()) / RAND_MAX;
    //cout << "Theta" << theta << endl;

    currentPosition.x = currentPosition.x + stepSize*cos(theta)*sin(phi);
    currentPosition.y = currentPosition.y + stepSize*sin(theta)*sin(phi);
    currentPosition.z = currentPosition.z + stepSize*cos(phi);
  }
  //cout <<  "x = " << currentPosition.x << ", y = " << currentPosition.y << endl;
}



void Randomwalk::selfAvoidingRandomStep(int n){

  //cout << "N = " << n << endl;
  //cout << "Step size = " << stepSize << endl;
  //cout << "Current position: " <<  "x = " << currentPosition.x << ", y = " << currentPosition.y << endl;

  if(n<=1){
    randomStep();
  }
  else{
    bool overlap = true;
    double theta = 0;
    double phi = 0;
    int startingPoint = 0;

    startingPoint = max(0, n-20);
    //cout << "Start " << startingPoint << endl;

    while(overlap){
      overlap = false;

      theta = (2 * M_PI * rand()) / RAND_MAX;
      phi = (M_PI * rand()) / RAND_MAX;
      newPosition.x = currentPosition.x + stepSize*cos(theta)*sin(phi);
      newPosition.y = currentPosition.y + stepSize*sin(theta)*sin(phi);
      newPosition.z = currentPosition.z + stepSize*cos(phi);
      //cout << "n = " <<n << endl;
      //cout <<  "x = " << newPosition.x << ", y = " << newPosition.y << ", z = " << newPosition.z << endl;

      for(int pos=startingPoint; pos<n; pos++){
        //cout << "Pos = " << pos << endl;
        double distance = pow(pow(newPosition.x-positions[pos].x,2)+
            pow(newPosition.y-positions[pos].y,2)+pow(newPosition.z-positions[pos].z,2),0.5);
        if(distance<stepSize){
          overlap = true;
          break;
        }
      }
    }
    currentPosition = newPosition;
  }
  //cout << "Current position: " <<  "x = " << currentPosition.x << ", y = " << currentPosition.y << endl;
  positions[n] = currentPosition;
}



double Randomwalk::calcEndDistance(){
  double distX = pow(currentPosition.x-startingPosition.x,2);
  double distY = pow(currentPosition.y-startingPosition.y,2);
  double distZ = pow(currentPosition.z-startingPosition.z,2);
  return distX + distY + distZ;
}


double Randomwalk::walk(int N){
  initializeParticle();

  if(not saw){
    for(int i=1; i<N+1; i++){
      randomStep();
    }
  }
  else{
    positions[0] = startingPosition;
    for(int i=1; i<N+1; i++){
      selfAvoidingRandomStep(i);
    }
  }
  return calcEndDistance();
}


void Randomwalk::varyN(){

  averageR = new double[nSteps];
  estimatedError = new double[nSteps];
  vecN = new int[nSteps];

  double sumR = 0;
  double sumR2 = 0;
  double dist = 0;
  double averageR2=0;


  for(int k=1; k<nSteps+1; k++){
    dist = 0;
    sumR = 0;
    sumR2 = 0;

    cout << "N = " << k << endl;

    for(int m=1; m<M+1; m++){
      dist = walk(k);
      sumR += dist;
      sumR2 += pow(dist,2);
    }

    vecN[k-1] = k;
    averageR[k-1] = sumR/M;
    averageR2 = sumR2/M;
    estimatedError[k-1] = sqrt(1.0/M*(averageR2-pow(averageR[M],2)));
  }

  if(not saw){
    sprintf(filename,"python_scripts/varyN_n%d_m%d.txt",nSteps,M);
  }
  else{
    sprintf(filename,"python_scripts/varyN_saw_n%d_m%d.txt",nSteps,M);
  }
  char header1[2] = "N";
  char header2[3] = "R2";
  char header3[4] = "err";
  save::save_to_text(header1, header2, header3, vecN, averageR, estimatedError, nSteps, filename);

  delete[] averageR;
  delete[] estimatedError;
  delete[] vecN;
}


void Randomwalk::varyM(){
  averageR = new double[M];
  estimatedError = new double[M];
  vecM = new int[M];

  double sumR = 0;
  double sumR2 = 0;
  double dist = 0;
  double averageR2=0;



  cout << "M, R2, err" << endl;

  for(int k=1; k<M+1; k++){

    dist = 0;
    sumR = 0;
    sumR2 = 0;

    for(int j=1; j<k; j++){
      dist = walk(nSteps);
      sumR += dist;
      sumR2 += pow(dist,2);
    }

    vecM[k-1] = k;
    averageR[k-1] = sumR/k;
    averageR2 = sumR2/k;

    estimatedError[k-1] = sqrt(1.0/k*(averageR2-pow(averageR[k],2)));

    //cout << "Mean R = " << averageR[k] << endl;
    //cout << "Mean R2 = " << averageR2 << endl;
    //cout << "(Mean R)2 = " << pow(averageR[k],2) << endl;
    //cout << "Err = " << estimatedError[k] << endl;
    //cout << k << ", " << averageR[k] << ", " << estimatedError[k] << endl;

  }

  sprintf(filename,"python_scripts/varyM_n%d_m%d.txt",nSteps, M);
  char header1[2] = "M";
  char header2[3] = "R2";
  char header3[4] = "err";
  save::save_to_text(header1, header2, header3, vecM, averageR, estimatedError, M, filename);

  delete[] averageR;
  delete[] estimatedError;
  delete[] vecM;

}
