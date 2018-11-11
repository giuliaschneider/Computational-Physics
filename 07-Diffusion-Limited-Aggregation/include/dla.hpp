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
  squarelattice *croppedLattice;
  bool croppedLat;
  Coordinates currentParticle;
  int time;
  Coordinates seedPos;
  double clusterRadius;
  double minRadius;
  double maxRadius;
  bool attached;
  bool outsideScoop;
  int leftmost;
  int rightmost;
  int topmost;
  int bottommost;


public:
  char filename[160];

public:
  dla(int nParticles);
  ~dla();
  void dlaSimulation();
  void saveSimulation();

private:
  void setSeed();
  void initializeParticle();
  void randomStep();
  double calcRadius();
  void calcMinMaxRadius();
  void checkMaxRadius();
  void checkAttached();
  void attachParticle();
  void cropLattice();
};


#endif
