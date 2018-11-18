/**
  CS-11
  @file     Randomwalk.cpp
  @author   Giulia Schneider
  @date     18.11.2018
  *version  1.0
  @brief    Performs a random walk in continuous space with fixed step size
            Possible flags:
            * randomwalk2D
            * randomwalk3D
            * selfAvoidingRandomWalk3D
*/

#include "Randomwalk.hpp"
#include "savedata.h"
#include <iostream>
#include <cstring>
#include <math.h>


using namespace std;


Randomwalk::Randomwalk(int nSteps, int M, char* method):
nSteps(nSteps), M(M), method(method){
  setStartingPosition();
  if(strcmp(method,"selfAvoidingRandomWalk3D")==0){
    positions = new Coordinates[nSteps];
  }
  varyN();
  //varyM();
}


Randomwalk::~Randomwalk(){
  if(method == "selfAvoidingRandomWalk3D"){
    delete[] positions;
  }
}


void Randomwalk::setStartingPosition(){
  /**
  * Initializes the starting position
  */
  startingPosition.x = 0;
  startingPosition.y = 0;
  startingPosition.z = 0;
}


void Randomwalk::initializeParticle(){
  /**
  * Initializes the particle, sets its position to the staring position
  */
  currentPosition.x = startingPosition.x;
  currentPosition.y = startingPosition.y;
  currentPosition.z = startingPosition.z;
}

double Randomwalk::calcEndDistance(){
  double dist = calcDistance(currentPosition, startingPosition);
  return dist;
}


double Randomwalk::calcDistance(Coordinates newPosition, Coordinates particlePosition){
  double xDist = pow(newPosition.x-particlePosition.x,2);
  double yDist = pow(newPosition.y-particlePosition.y,2);
  double zDist = pow(newPosition.z-particlePosition.z,2);
  double distance = pow(xDist+yDist+zDist,0.5);
  return distance;
}

void Randomwalk::randomStep2D(){
  /**
  * Performs a random step in 2D
  */
  double theta = (2 * M_PI * rand()) / RAND_MAX;
  currentPosition.x = currentPosition.x + stepSize*cos(theta);
  currentPosition.y = currentPosition.y + stepSize*sin(theta);
  currentPosition.z = currentPosition.z;
}

void Randomwalk::randomStep3D(){
  /**
  * Performs a random step in 3D
  */
  double theta = (2 * M_PI * rand()) / RAND_MAX;
  double phi = (M_PI * rand()) / RAND_MAX;

  currentPosition.x = currentPosition.x + stepSize*cos(theta)*sin(phi);
  currentPosition.y = currentPosition.y + stepSize*sin(theta)*sin(phi);
  currentPosition.z = currentPosition.z + stepSize*cos(phi);
}

double Randomwalk::randomwalk2D(int nSteps){
  /**
  * Performs a random walk with nSteps in 2D space
  */
  initializeParticle();

  for(int i=0; i<nSteps; i++){
    randomStep2D();
  }
  return calcEndDistance();
}

double Randomwalk::randomwalk3D(int nSteps){
  /**
  * Performs a random walk with nSteps in 2D space
  * @param nSteps: number of steps
  */
  initializeParticle();

  for(int i=0; i<nSteps; i++){
    randomStep3D();
  }
  return calcEndDistance();
}


void Randomwalk::selfAvoidingRandomStep3D(int n){
  /**
  * Performs a random step, such that the particle doesn't overlap with
    previous particles
  * @param n: nth particle
  */
  if(n<=1){
    randomStep3D();
  }
  else{
    bool overlap = true;
    double theta = 0;
    double phi = 0;
    int iter = 0;
    int maxIter = 1000;

    while(overlap and iter<maxIter){
      overlap = false;
      theta = double((2.0 * M_PI * rand()) / RAND_MAX);
      phi = double((M_PI * rand()) / RAND_MAX);
      newPosition.x = currentPosition.x + stepSize*cos(theta)*sin(phi);
      newPosition.y = currentPosition.y + stepSize*sin(theta)*sin(phi);
      newPosition.z = currentPosition.z + stepSize*cos(phi);
      iter++;
      for(int pos=0; pos<n; pos++){
        double distance = calcDistance(newPosition, positions[pos]);
        if(distance<stepSize){
          overlap = true;
          break;
        }
      }
    }
    if(iter>maxIter){
      converged = false;
    }
    else{converged = true;}
    currentPosition = newPosition;
  }
  positions[n-1] = currentPosition;
}


double Randomwalk::selfAvoidingRandomWalk3D(int nSteps){
  /**
  * Performs a self avoiding random walk with nSteps in 2D space
  * @param nSteps: number of steps
  */
  initializeParticle();
  positions = new Coordinates[nSteps];
  positions[0] = startingPosition;
  converged = false;

  while(!converged){
    converged = true;
    for(int i=1; i<nSteps+1; i++){
      selfAvoidingRandomStep3D(i);
      if(!converged){
        break;
      }
    }
  }
  delete[] positions;
  return calcEndDistance();
}


void Randomwalk::varyN(){
  /**
  * Performs a random walk for different number of steps (1 to nSteps)
    and saves them to a text file
  */
  // Initialize variables
  averageR2 = new double[nSteps];
  estimatedError = new double[nSteps];
  vecN = new int[nSteps];
  double sumR2 = 0;
  double sumR22 = 0;
  double dist = 0;
  double averageR22=0;
  // Loop through different number of spheres
  for(int n=1; n<nSteps+1; n++){
    cout << "N = " << n << endl;
    dist = 0;
    sumR2 = 0;
    sumR22 = 0;
    // Generate different configurations
    for(int m=1; m<M+1; m++){
      if(strcmp(method,"randomwalk2D")==0){
        dist = randomwalk2D(n);
      }
      else if(strcmp(method,"randomwalk3D")==0){
        dist = randomwalk3D(n);
      }
      else{
        dist = selfAvoidingRandomWalk3D(n);
      }
      sumR2 += pow(dist,2);
      sumR22 += pow(dist,4);
    }
    // Save results in vector
    vecN[n-1] = n;
    averageR2[n-1] = sumR2/M;
    averageR22 = sumR22/M;
    estimatedError[n-1] = sqrt(1.0/M*(averageR22-pow(sumR2/M,2)));
  }
  // Save results to txt
  sprintf(filename,"results/varyN_%s_n%d_m%d.txt",method,nSteps,M);
  char header1[2] = "N";
  char header2[3] = "R2";
  char header3[4] = "err";
  save_to_text(header1, header2, header3, vecN, averageR2, estimatedError, nSteps, filename);
  // Delete dynamic arrays
  delete[] averageR2;
  delete[] estimatedError;
  delete[] vecN;
}


void Randomwalk::varyM(){
  /**
  * Performs a random walk for different number of configurations (1 to M)
    and saves them to a text file
  */
  // Initialize variables
  averageR2 = new double[M];
  estimatedError = new double[M];
  vecM = new int[M];
  double sumR2 = 0;
  double sumR22 = 0;
  double dist = 0;
  double averageR22=0;
  // Loop through number of configurations
  for(int k=1; k<M+1; k++){
    cout << "M = " << k << endl;
    dist = 0;
    sumR2 = 0;
    sumR22 = 0;
    for(int j=1; j<k; j++){
      if(strcmp(method,"randomwalk2D")==0){
        dist = randomwalk2D(nSteps);
      }
      else if(strcmp(method,"randomwalk3D")==0){
        dist = randomwalk3D(nSteps);
      }
      else{
        dist = selfAvoidingRandomWalk3D(nSteps);
      }
      sumR2 += pow(dist,2);
      sumR22 += pow(dist,4);
    }
    // Save results in vector
    vecM[k-1] = k;
    averageR2[k-1] = sumR2/k;
    averageR22 = sumR22/k;
    estimatedError[k-1] = sqrt(1.0/k*(averageR22-pow(sumR2/k,2)));

    //cout << "Mean R = " << averageR[k] << endl;
    //cout << "Mean R2 = " << averageR2 << endl;
    //cout << "(Mean R)2 = " << pow(averageR[k],2) << endl;
    //cout << "Err = " << estimatedError[k] << endl;
    //cout << k << ", " << averageR[k] << ", " << estimatedError[k] << endl;
  }
  // Save results to txt
  sprintf(filename,"results/varyM_%s_n%d_m%d.txt",method,nSteps,M);
  char header1[2] = "M";
  char header2[3] = "R2";
  char header3[4] = "err";
  save_to_text(header1, header2, header3, vecM, averageR2, estimatedError, M, filename);
  // Delete dynamic arrays
  delete[] averageR2;
  delete[] estimatedError;
  delete[] vecM;
}
