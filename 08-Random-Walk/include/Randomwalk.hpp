#ifndef RANDOMWALK
#define RANDOMWALK

#include <string>


struct Coordinates{
  double x;
  double y;
  double z;
};


class Randomwalk{
private:
  int nSteps;
  int M;
  char* method;
  int stepSize = 1;
  Coordinates startingPosition;
  Coordinates currentPosition;
  Coordinates newPosition;
  int* vecM;
  int* vecN;
  double* averageR;
  double* estimatedError;
  Coordinates* positions;

public:
  char filename[160];

public:
  Randomwalk(int nSteps, int M, char* method);
  ~Randomwalk();

private:
  void setStartingPosition();
  void initializeParticle();
  double calcEndDistance();
  double calcDistance(Coordinates newPosition, Coordinates particlePosition);
  void randomStep2D();
  void randomStep3D();
  double randomwalk2D(int nSteps);
  double randomwalk3D(int nSteps);
  void selfAvoidingRandomStep3D(int n);
  double selfAvoidingRandomWalk3D(int nSteps);
  void varyN();
  void varyM();

};


#endif
