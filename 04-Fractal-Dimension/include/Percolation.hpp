
#ifndef PERCOLATION
#define PERCOLATION

#include<vector>

class Percolation{
public:
  const int ImageWidth;
  const int ImageHeight;
private:
  double p;
  double z;
  int N;
  char filename[160];
  char filename_png[160];
  int kmax;
  int Mmax;
  std::vector<int> M;
  std::vector<int> nClusters;
public:
  int *lat;
public:
  Percolation(int N);
  Percolation(int N, double p);
  ~Percolation();

  void calc_different_p();
  void saveFigure(char *filename);
  void calc_ClusterSizeDistribution();
  void calcCSD_different_p();
  void find_largestCluster();
  int* getLattice();
  void printLattice();
private:
  void createLattice(double p,int color);
  void checkNeighbors(int position);
  void set_k(int position);
  void found_newCluster(int &position);
  void updateM(int k);
  void countClusters();
};

#endif
