/**
  CS-11
  @file     squarelattice.cpp
  @author   Giulia Schneider
  @date     06.10.2018
  *version  1.0
  @brief    Defines a square lattice of size L*L
*/


#include "squarelattice.hpp"
#include <string>
#include<iostream>
#include <iomanip>      // std::setw
#include<fstream>
#include <cstdlib>


#define ImageWidth 1000  //image width
#define ImageHeight 1000 //image height



using namespace std;


squarelattice::squarelattice(int L):
L(L){
  cout << "Construction Square" << endl;

  N = L*L;
  sites = new int[N]();
}

squarelattice::~squarelattice(){
  delete[] sites;
}



int squarelattice::getPosition(Coordinates crd){
  return crd.y*L + crd.x;
}


void squarelattice::setValue(int position, int value){
  sites[position] = value;
}

void squarelattice::setValue(Coordinates crd, int value){
  int position = getPosition(crd);
  sites[position] = value;
}


int squarelattice::getValue(int position){
  return sites[position];
}

int squarelattice::getValue(Coordinates crd){
  int position = getPosition(crd);
  return sites[position];
}


void squarelattice::getNeighbors(Coordinates crd){
  int position = getPosition(crd);
  getNeighbors(position);
}


void squarelattice::getNeighbors(int position){
  if(position < L){ // upper boundary
    north = -1;
    south = position+L;
  }
  else if(position >= (L*(L-1))){ //lower boundary
    north = position-L;
    south = -1;
  }
  else { // not on boundary
    north = position-L;
    south = position+L;
  }

  if(position%L == 0){ // eastern boundary
    east = -1;
    west = position+1;
  }
  else if(position%L == (L-1)){ //western boundary
    east = position-1;
    west = -1;
  }
  else { // not on boundary
    east = position-1;
    west = position+1;
  }
}


void squarelattice::getEasternNeighbor(int position){
  if(position%L == 0){ // eastern boundary
    east = -1;
  }
  else{
    east = position-1;
  }
}

void squarelattice::getNorthernNeighbor(int position){
  if(position < L){ // eastern boundary
    north = -1;
  }
  else{
    north = position-L;
  }
}


void squarelattice::getPeriodicNeighbors(Coordinates crd){
  int position = getPosition(crd);
  getNeighbors(position);
}


void squarelattice::getPeriodicNeighbors(int position){
  if(position < L){ // upper boundary
    north = (L*(L-1)) + position;
    south = position+L;
  }
  else if(position >= (L*(L-1))){ //lower boundary
    north = position-L;
    south = position%L;
  }
  else { // not on boundary
    north = position-L;
    south = position+L;
  }

  if(position%L == 0){ // eastern boundary
    east = position + (L-1);
    west = position+1;
  }
  else if(position%L == (L-1)){ //western boundary
    east = position-1;
    west = position - (L-1);
  }
  else { // not on boundary
    east = position-1;
    west = position+1;
  }
}

void squarelattice::getNeighboringValues(int position){
  getNeighbors(position);
  /*
  cout << "North " << north << ", " << sites[north] << endl;
  cout << "South " << south << ", " << sites[south]<< endl;
  cout << "East " << east << ", " << sites[east]<< endl;
  cout << "West " << west << ", " << sites[west]<< endl;
  */

  if(north==-1){neighboringValues[0] = 0;}
  else{neighboringValues[0] = sites[north];}

  if(south==-1){neighboringValues[1] = 0;}
  else{neighboringValues[1] = sites[south];}

  if(east==-1){neighboringValues[2] = 0;}
  else{neighboringValues[2] = sites[east];;}

  if(west==-1){neighboringValues[3] = 0;}
  else{neighboringValues[3] = sites[west];}

}



void squarelattice::getNeighboringValues(Coordinates crd){
  int position = getPosition(crd);
  getNeighboringValues(position);
}


int squarelattice::getEasternValue(int position){
  getEasternNeighbor(position);

  if(east==-1){return 0;}
  else{return sites[east];}
}


int squarelattice::getNorthernValue(int position){
  getNorthernNeighbor(position);

  if(north==-1){return 0;}
  else{return sites[north];}
}


void squarelattice::getPeriodicNeighboringValues(int position){
  getPeriodicNeighbors(position);
  /*
  cout << "North " << north << ", " << sites[north] << endl;
  cout << "South " << south << ", " << sites[south]<< endl;
  cout << "East " << east << ", " << sites[east]<< endl;
  cout << "West " << west << ", " << sites[west]<< endl;
  */

  neighboringValues[0] = sites[north];
  neighboringValues[1] = sites[south];
  neighboringValues[2] = sites[east];
  neighboringValues[3] = sites[west];
}

void squarelattice::getPeriodicNeighboringValues(Coordinates crd){
  int position = getPosition(crd);
  getPeriodicNeighboringValues(position);
}


void squarelattice::printLattice(){
  cout << "Printing" << endl;
  for(int i=0;i<(N);i++){
    cout <<  setw(2);
    if(i%L==L-1){
      cout << sites[i] << "|" << endl;
    }
    else{
      cout <<  sites[i] << "|"<< flush;
    }
  }
}

void squarelattice::printVector(){
  /* Print data array to console */
  for(int i=0;i<N;i++){
      cout << sites[i] << endl;
  }
}


void squarelattice::saveLattice(const char* vfilename){
  ofstream outFile;
  outFile.open(vfilename);

  if(outFile.is_open()){
    outFile.setf(ios::fixed, ios::floatfield);
    outFile.precision(2);
    for(int i=0; i < N; i++)
    outFile << sites[i] << endl;
    outFile.close();
  }
  else {
    cout << "Could not create file: " << vfilename << endl;
  }
}



void squarelattice::saveToPPM(const string& vfilename,  int* r, int* g, int* b){
  int  i, j, k, l;
  int vwidth = ImageWidth;
  int vheight = ImageHeight;
  int vw= vwidth/L, vh=vheight/L;

  ofstream out (vfilename);

  out << "P3" << endl;
  out << vw*L << " " << vh*L << endl;
  out << "255" << endl;

  for (i=0; i<L; i++)
    for (j=0; j<vh; j++)
      for (k=0; k<L; k++)
      {
        for (l=0; l<vw; l++)
        { out << r[sites[k+i*L]] << " " << g[sites[k+i*L]];
          out << " " << b[sites[k+i*L]] << " ";
        }
      }
      out << endl;
  out.close ();
}


void squarelattice::saveToPng(const string& filename, int* r, int* g, int* b){
  string filename_ppm;
  filename_ppm = filename;
  filename_ppm.erase (filename_ppm.end()-4, filename_ppm.end());
  filename_ppm += ".ppm";
  saveToPPM(filename_ppm, r, g, b);


  // rm automatically deletes the ppm-file to save memory
  char cmd[160];
  sprintf(cmd,"convert %s %s; rm -f %s",
          filename_ppm.c_str(), filename.c_str(), filename_ppm.c_str());
  system(cmd);
}
