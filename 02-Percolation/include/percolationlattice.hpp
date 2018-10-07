
#ifndef PERCOLATIONLATTICE
#define PERCOLATIONLATTICE

#include "squarelattice.hpp"


class percolationlattice{
public:
  //const int ImageWidth;
  //const int ImageHeight;
private:
  double p;
  double z;
  int L;
  int N;
  char filename[160];
  char filename_png[160];
public:
  squarelattice *lat;
  int neighbors[4];
public:
  percolationlattice(int L);
  percolationlattice(int L, double p);
  ~percolationlattice();

  void setValue(int position, int value);
  int getValue(int position);
  int* getNeighboringValues(int position);
  int* getNeighbors(int position);
  void setLattice(double p,int color);
  void saveFigure(char *filename, int* r, int* g, int* b);

  void setLattice_differentProbabilities();
};

#endif
