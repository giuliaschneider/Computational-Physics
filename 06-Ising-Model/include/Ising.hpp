#ifndef ISING
#define ISING

#include "squarelattice.hpp"

class Ising{
private:
  int L;
  int N;
  double kbT;
  double J;
  squarelattice* lat;
  int E;
  int M;
  int nSweeps;
public:
  char filename[160];
  int* vecE;
  int* vecM;
private:
  void initializeLattice();
  int calcH(int position);
  void calcEM();
  void systemSweep();
  void singleFlip(int position);
  void simulation();
public:
  Ising(int L, double T, double J, int nSweeps);
  ~Ising();
};

#endif
