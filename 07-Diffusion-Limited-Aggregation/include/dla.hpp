
#ifndef DLA
#define DLA

#include "squarelattice.hpp"



enum StepDirection	{ N, E, S, W };	// compass points



class dla{
private:
  int nParticles;
  int L;
  int N;
  squarelattice *lattice;
  Coordinates currentParticle;
  int time;
  Coordinates seedPos;
  double clusterRadius;
  double minRadius;
  double maxRadius;
  bool attached;
  bool outsideScoop;


public:
  char filename[160];

public:
  dla(int nParticles);
  ~dla();

private:
  void setSeed();
  void initializeParticle();
  void randomStep();
  void dlaSimulation();
  double calcRadius();
  void calcMinMaxRadius();
  void checkMaxRadius();
  bool checkNeighboringSites();
  void checkAttached();


};


#endif
