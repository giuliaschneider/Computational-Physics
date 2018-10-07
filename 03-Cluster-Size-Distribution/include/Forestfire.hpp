#ifndef FORESTFIRE
#define FORESTFIRE

#include "Percolation.hpp"

class Forestfire{

public:
  static const int size_p_array = 101;
private:
  double p;
  double z;
  int N;
  Percolation Forest;
  char filename[160];
  int t;
  int neighborNorth;
  int neighborEast;
  int neighborSouth;
  int neighborWest;
  bool burntNeighbor;
  bool burntNeighbor_thisTimeStep;
  bool bottom_reached;
  int shortest_path;
  int lifeTime;
  //int *vec_spanningCluster;
  //int *vec_shortest_path;
  //int *vec_lifeTime;
  double avg_spanningCluster;
  double avg_shortest_path;
  double avg_lifeTime;
  double vec_p_spanningCluster[size_p_array];
  double vec_p_shortest_path[size_p_array];
  double vec_p_lifeTime[size_p_array];
private:
  void startFire();
  void burnNeighbors(int position, int t);
  void printFire(int &vlx, int &vly, const int &vwidth, const int &vheight, int &t, const char* vfilename="output.ppm");
public:
  Forestfire(int N);
  ~Forestfire();
  void BurningMethod(bool printFigures);
  void FireStatistics(int n_experiments);
  void FireStatistics_different_p(int n_experiments);
};

#endif
