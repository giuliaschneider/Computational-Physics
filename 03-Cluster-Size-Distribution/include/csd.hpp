
#ifndef CSD
#define CSD

#include<vector>
#include "percolationlattice.hpp"


class csd{
public:
  double p;
  double z;
  int L;
  char filename[160];
  char filename_png[160];
  int kmax;
  int Mmax;
  std::vector<int> M;
  std::vector<int> nClusters;
  int eastValue;
  int northValue;
public:
  percolationlattice* lat;
public:
  csd(int L, double p);
  ~csd();
  void calcCSD();
  void calcCSD_different_p();
  squarelattice* find_largestCluster();
private:
  void set_k(int position);
  void found_newCluster(int position);
  void updateM(int k);
  void countClusters();
};

#endif
