


#include "squarelattice.hpp"
#include<iostream>
#include <iomanip>      // std::setw
#include<fstream>


using namespace std;


squarelattice::squarelattice(int L):
L(L){
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



void squarelattice::getNeighbors(Coordinates crd){
  int position = getPosition(crd);
  getNeighbors(position);
}


void squarelattice::getNeighbors(int position){
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

  neighboringValues[0] = sites[north];
  neighboringValues[1] = sites[south];
  neighboringValues[2] = sites[east];
  neighboringValues[3] = sites[west];
}

void squarelattice::getNeighboringValues(Coordinates crd){
  int position = getPosition(crd);
  getNeighboringValues(position);
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



void squarelattice::printToPPM(const char* vfilename){
  int  i, j, k, l;
  int vwidth = L;
  int vheight = L;
  int vw= vwidth/L, vh=vheight/L;
  int r[10], g[10], b[10];

  r[0]= 255; g[0]= 255; b[0]= 255; //white  use 0 in your lattice if you want to color it white
  r[1]=   0; g[1]=   0; b[1]=   0; //green  use 1 in your lattice if you want to color it green
  r[2]=  98; g[2]=  62; b[2]=  39; //red
  r[3]= 126; g[3]=  80; b[3]=  51; //black
  r[4]= 145; g[4]=  84; b[4]=  54; //blue
  r[5]= 149; g[5]=  95; b[5]=  60; //blue
  r[6]= 196; g[6]= 124; b[6]=  79; //blue
  r[7]= 220; g[7]= 139; b[7]=  89; //blue
  r[8]= 255; g[8]= 176; b[8]= 112; //blue
  r[9]= 255; g[9]= 195; b[9]= 124; //blue
  ofstream out (vfilename);

  out << "P3" << endl;
  out << vw*L << " " << vh*L << endl;
  out << "255" << endl;

  for (i=0; i<L; i++)
    for (j=0; j<vh; j++)
      for (k=0; k<L; k++)
      {
        for (l=0; l<vw; l++)
        { out << r[sites[k+i*L]] << " " << g[sites[k+i*L]] << " " << b[sites[k+i*L]] << " ";
        }
      }
      out << endl;

  out.close ();
}
