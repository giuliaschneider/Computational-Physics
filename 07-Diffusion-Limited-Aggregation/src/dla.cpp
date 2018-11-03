/**
  CS-11
  @file     dla.cpp
  @author   Giulia Schneider
  @date     03.05.2018
  *version  1.0
  @brief    Generates a lattice with randomly occupied and unoccupied sites
            according to the occupation probability p
*/

#include "dla.hpp"
#include "savedata.hpp"
#include "latticeview.h"
#include <iostream>
#include <iomanip>      // std::setw
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <math.h>


using namespace std;


dla::dla(int nParticles): nParticles(nParticles){
  double factor = 1.0/log(pow(nParticles,2.2));
  L = int(factor*nParticles);
  N = L*L;
  lattice = new squarelattice(L);
  dlaSimulation();
}


dla::~dla(){
  delete lattice;
}


void dla::setSeed(){
  seedPos.x = int(L/2);
  seedPos.y = int(L/2);
  lattice->setValue(seedPos, time);
  clusterRadius = 0;
  calcMinMaxRadius();

  //cout << "Seed " << seedPos.x << ", " << seedPos.y << endl;
  //cout << "     " << lattice->getPosition(seedPos) << endl;


}


void dla::initializeParticle(){
  double theta = (2 * M_PI * rand()) / RAND_MAX;

  currentParticle.x = seedPos.x + minRadius*cos(theta);
  currentParticle.y = seedPos.y + minRadius*sin(theta);

  attached = false;
  outsideScoop = false;

  //cout << "Particle " << currentParticle.x << ", " << currentParticle.y << endl;
  //cout << "        " << lattice->getPosition(currentParticle) << endl;

}


void dla::randomStep(){

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

  //cout << "Time = " << time << ", x = " << currentParticle.x << ", y = " << currentParticle.y << endl;
  //cout << "        " << lattice->getPosition(currentParticle) << endl;


}


void dla::calcMinMaxRadius(){
  minRadius = clusterRadius+2;
  maxRadius = min(L/2.0-1, max(2*clusterRadius, minRadius+5));
}

double dla::calcRadius(){
  double distX = pow(currentParticle.x-seedPos.x,2);
  double distY = pow(currentParticle.y-seedPos.y,2);
  double radius = sqrt(distX + distY);
  return radius;
}


void dla::checkMaxRadius(){
  double radius = calcRadius();
  if(radius > maxRadius){
    //cout << "Outside " << endl;

    initializeParticle();
    outsideScoop = true;
  }
}



bool dla::checkNeighboringSites(){
  lattice->getNeighboringValues(currentParticle);
  bool hasNeighbor = false;
  for(int i=0; i<4; i++){
    //cout << "Neighbor " << lattice->neighboringValues[i] << endl;
    if(lattice->neighboringValues[i] != 0){
      hasNeighbor = true;
    }
  }
  return hasNeighbor;
}

void dla::checkAttached(){

  lattice->getNeighboringValues(currentParticle);
  bool hasNeighbor = checkNeighboringSites();

  if(hasNeighbor){
    attached = true;
    //cout << "Attached " << endl;
    lattice->setValue(currentParticle, min(int(time*9.0/nParticles+1),9));
    cout << min(int(time*9.0/nParticles+1),9) << endl;
    //cout << "Time = " << time << ", x = " << currentParticle.x << ", y = " << currentParticle.y << endl;


    double radius = calcRadius();
    if(radius > clusterRadius){
      clusterRadius = radius;
      calcMinMaxRadius();
    }
  }
}


void dla::dlaSimulation(){

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
  }

  char filename [160];
  sprintf(filename,"python_scripts/dla_n%d.ppm",nParticles);
  //lattice->printLattice();
  lattice->printToPPM(filename);


}
