
#ifndef ISING
#define ISING


class Ising{
private:
  int L;
  int N;
  double kbT;
  double J;
  int* spins;
  int E;
  int M;
  int north;
  int south;
  int east;
  int west;
  int nSweeps;
private:
  void initializeLattice();
  void getNeighbors(int position);
  void calcEM();
  void systemSweep();
  void singleFlip(int position);
  void simulation();
public:
  char filename[160];
  int* vecE;
  int* vecM;
public:
  Ising(int L, double T, double J, int nSweeps);
  ~Ising();


};


#endif
