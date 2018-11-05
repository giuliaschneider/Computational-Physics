
#ifndef RANDOMWALK
#define RANDOMWALK


struct Coordinates{
  double x;
  double y;
  double z;
};


class Randomwalk{
private:
  int nSteps;
  int M;
  bool d2;
  bool saw;
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
  Randomwalk(int nSteps, int M, bool d2 = true, bool saw = false);
  ~Randomwalk();

private:
  void setStartingPosition();
  void initializeParticle();
  void randomStep();
  void selfAvoidingRandomStep(int n);
  double calcEndDistance();
  double walk(int N);
  void varyN();
  void varyM();

};


#endif
