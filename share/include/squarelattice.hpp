
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
  int ne;
  int nw;
  int se;
  int sw;
  int neighboringValues[4];
  int neighborsPositions[8];


public:
  squarelattice(int L);
  ~squarelattice();

  int getLatticeSize();
  void setValue(int position, int value);
  void setValue(Coordinates crd, int value);
  int getValue(int position);
  int getValue(Coordinates crd);


  void getNeighbors(Coordinates crd);
  void getNeighbors(int position);
  void getNeighbors(int position, int offset);

  void getPeriodicNeighbors(Coordinates crd);
  void getPeriodicNeighbors(int position);
  void getEasternNeighbor(int position);
  void getNorthernNeighbor(int position);
  void getDiagonalNeighbors(int position);
  void getDiagonalNeighbors(int position, int offset);

  int* get8NeigboringPositions(int position);
  int* get8NeigboringPositions(int position, int offset);

  void getNeighboringValues(int position);
  void getNeighboringValues(Coordinates crd);
  int* returnNNeighboringValues(int position);
  int* returnNNeighboringValues(Coordinates crd);

  void getPeriodicNeighboringValues(int position);
  void getPeriodicNeighboringValues(Coordinates crd);
  int* returnNPeriodicNeighboringValues(int position);
  int* returnNPeriodicNeighboringValues(Coordinates crd);
  
  int getEasternValue(int position);
  int getNorthernValue(int position);

  int getPosition(Coordinates crd);
  void printCoordinates(int position);

  void printLattice();
  void printVector();
  void saveLattice(const char* vfilename);
  void saveToPPM(const std::string& vfilename, int* r, int* g, int* b);
  void saveToPng(const std::string& filename, int* r, int* g, int* b);

private:

};


#endif
