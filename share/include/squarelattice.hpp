
#ifndef SQUARELATTICE
#define SQUARELATTICE

#include <string>

struct Coordinates{
  int x;
  int y;
};


class squarelattice{
private:
  int L;
  int N;

public:
  int* sites;
  int north;
  int south;
  int east;
  int west;
  int neighboringValues[4];

public:
  squarelattice(int L);
  ~squarelattice();
  void setValue(int position, int value);
  void setValue(Coordinates crd, int value);
  int getValue(int position);
  int getValue(Coordinates crd);


  void getNeighbors(Coordinates crd);
  void getNeighbors(int position);
  void getPeriodicNeighbors(Coordinates crd);
  void getPeriodicNeighbors(int position);
  void getEasternNeighbor(int position);
  void getNorthernNeighbor(int position);

  void getNeighboringValues(int position);
  void getNeighboringValues(Coordinates crd);
  void getPeriodicNeighboringValues(int position);
  void getPeriodicNeighboringValues(Coordinates crd);
  int getEasternValue(int position);
  int getNorthernValue(int position);

  int getPosition(Coordinates crd);

  void printLattice();
  void printVector();
  void saveLattice(const char* vfilename);
  void saveToPPM(const std::string& vfilename, int* r, int* g, int* b);
  void saveToPng(const std::string& filename, int* r, int* g, int* b);

private:

};


#endif
