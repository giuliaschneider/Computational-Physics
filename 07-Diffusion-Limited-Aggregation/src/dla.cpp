/**
  CS-11
  @file     dla.cpp
  @author   Giulia Schneider
  @date     03.11.2018
  *version  1.0
  @brief    Generates a lattice with randomly occupied and unoccupied sites
            according to the occupation probability p
*/

#include "dla.hpp"
#include "savedata.h"
#include <iostream>
//#include <string>
#include <math.h>



using namespace std;


dla::dla(int nParticles): nParticles(nParticles){

  // Generate 2D lattice dynamically
  double factor = 0.0;
  if(nParticles<10000){
    factor = 0.5+1/log(nParticles);
  }
  else{
    factor = 1.0/log(pow(nParticles,2.2));
  }
  cout << "Factor " << factor << endl;
  L = int(factor*nParticles);
  N = L*L;
  lattice = new squarelattice(L);
}


dla::~dla(){
  delete lattice;
  if(croppedLat){delete croppedLattice;}
}


void dla::setSeed(){
  /**
  * Sets a seed point to the lattice center
  */
  seedPos.x = int(L/2);
  seedPos.y = int(L/2);
  lattice->setValue(seedPos, time);
  clusterRadius = 0;
  calcMinMaxRadius();
  topmost = seedPos.y;
  bottommost = seedPos.y;
  leftmost = seedPos.x;
  rightmost = seedPos.x;
}


void dla::initializeParticle(){
  /**
  * Randomly creates a particle on the starting circle
  */
  double theta = (2 * M_PI * rand()) / RAND_MAX;
  currentParticle.x = seedPos.x + minRadius*cos(theta);
  currentParticle.y = seedPos.y + minRadius*sin(theta);
  attached = false;
  outsideScoop = false;
}


void dla::randomStep(){
  /**
  * Performs a random step to either the N/S/E/W-direction
  */
	StepDirection step = StepDirection(rand() %4);
	switch( step )	{
	  case 0:
        currentParticle.x--;
        break;
		case 1:
        currentParticle.y++;
        break;
		case 2:
        currentParticle.x++;
        break;
		case 3:
        currentParticle.y--;
        break;
	}
}


void dla::calcMinMaxRadius(){
  /**
  * Calculates the starting and maximal radius
    Starting radius: from where the random walker starts
    Maximal radius: random walk is stopped
  */
  minRadius = clusterRadius+2;
  maxRadius = min(L/2.0-1, max(2*clusterRadius, minRadius+5));
}

double dla::calcRadius(){
  /**
  * Calculates the radius from the current random walker to the seed
  * Return: radius
  */
  double distX = pow(currentParticle.x-seedPos.x,2);
  double distY = pow(currentParticle.y-seedPos.y,2);
  double radius = sqrt(distX + distY);
  return radius;
}


void dla::checkMaxRadius(){
  /**
  * Checks if the current random walker is outside the maximal radius
  */
  double radius = calcRadius();
  if(radius > maxRadius){
    initializeParticle();
    outsideScoop = true;
  }
}

void dla::checkAttached(){
  /**
  * Checks if the current random walker is attached
  */
  lattice->getNeighboringValues(currentParticle);
  bool hasNeighbor = false;
  for(int i=0; i<4; i++){
    //cout << "Neighbor " << lattice->neighboringValues[i] << endl;
    if(lattice->neighboringValues[i] != 0){
      hasNeighbor = true;
      break;
    }
  }
  if(hasNeighbor){
    attached = true;
  }
}


void dla::attachParticle(){
  /**
  * Sets the lattice position of the current particle to the current time
    Updates the starting and maximal radius
  */
  lattice->setValue(currentParticle, min(int(time*9.0/nParticles+1),9));
  double radius = calcRadius();
  if(radius > clusterRadius){
    clusterRadius = radius;
    calcMinMaxRadius();
  }
  topmost = min(currentParticle.y, topmost);
  bottommost = max(currentParticle.y, bottommost);
  leftmost = min(currentParticle.x,leftmost);
  rightmost = max(currentParticle.x, rightmost);
}


void dla::dlaSimulation(){
  /**
  * Simulates the dla process for nParticles
  */
  time = 1;
  setSeed();
  for(int i=0; i<nParticles; i++){
    time ++;
    initializeParticle();
    while(not attached){
      randomStep();
      checkMaxRadius();
      checkAttached();
    }
    attachParticle();
    if(topmost<=0 or bottommost>=L or leftmost<=0 or rightmost>=L){
      break;
    }
  }
  cropLattice();
  saveSimulation();
}

void dla::cropLattice(){
  Coordinates pos = seedPos;
  int xPos = max(seedPos.x-maxRadius, 0.0);
  int yPos = max(seedPos.y-maxRadius, 0.0);
  pos.x = xPos;
  pos.y = yPos;
  int cropPosition = lattice->getPosition(pos);
  int croppedL = 2*maxRadius;

  croppedLattice = new squarelattice(croppedL);
  int row = 0;
  for(int i=0; i<(croppedL*croppedL); i++){
    row = i/croppedL;
    croppedLattice->setValue(i, lattice->getValue(cropPosition+(row*L)+i%croppedL));
  }
  saveSimulation();
}


void dla::saveSimulation(){
  /**
  * Saves the current simulation as png
  */
  int r[10], g[10], b[10];
  r[0]= 255; g[0]= 255; b[0]= 255;
  r[1]=   0; g[1]=   0; b[1]=   0;
  r[2]=  98; g[2]=  62; b[2]=  39;
  r[3]= 126; g[3]=  80; b[3]=  51;
  r[4]= 145; g[4]=  84; b[4]=  54;
  r[5]= 149; g[5]=  95; b[5]=  60;
  r[6]= 196; g[6]= 124; b[6]=  79;
  r[7]= 220; g[7]= 139; b[7]=  89;
  r[8]= 255; g[8]= 176; b[8]= 112;
  r[9]= 255; g[9]= 195; b[9]= 124;

  sprintf(filename,"results/dla_n%d.png",nParticles);
  croppedLattice->saveToPng(filename, r, g, b);
}
