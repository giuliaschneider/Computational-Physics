
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
public:
  percolationlattice(int L);
  percolationlattice(int L, double p);
  ~percolationlattice();
  void setLattice(double p,int color);
  void calc_different_p();
  void saveFigure(char *filename);
};

#endif
