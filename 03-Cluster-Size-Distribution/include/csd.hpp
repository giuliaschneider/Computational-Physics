
#ifndef CSD
#define CSD

#include<vector>

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
public:
  percolationlattice lat;
public:
  csd(int N, double p);
  ~csd();
  void calcCSD();
  void calcCSD_different_p();
private:
  void set_k(int position);
  void found_newCluster(int &position);
  void updateM(int k);
  void countClusters();
};

#endif
