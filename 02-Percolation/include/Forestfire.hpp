#ifndef FORESTFIRE
#define FORESTFIRE

#include "percolationlattice.hpp"




class Forestfire{

public:
  static const int size_p_array = 101;
private:
  double p;
  double z;
  int L;
  percolationlattice* Forest;
  char filename[160];
  int t;
  int* neighbors;
  int* neighboringValues;
  bool burntNeighbor;
  bool burntNeighbor_thisTimeStep;
  bool bottom_reached;
  int shortest_path;
  int lifeTime;
  double avg_spanningCluster;
  double avg_shortest_path;
  double avg_lifeTime;
  double vec_p_spanningCluster[size_p_array];
  double vec_p_shortest_path[size_p_array];
  double vec_p_lifeTime[size_p_array];
private:
  void startFire();
  void burnNeighbors(int position, int t);
  void stats(int n_experiments);
public:
  Forestfire(int N, double p);
  ~Forestfire();
  void BurningMethod(bool printFigures);
  void stats_differentProbabilities(int n_experiments);
};

#endif
