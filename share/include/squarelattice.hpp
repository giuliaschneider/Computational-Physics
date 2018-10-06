
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
  void getNeighbors(Coordinates crd);
  void getNeighbors(int position);
  void getNeighboringValues(int position);
  void getNeighboringValues(Coordinates crd);

  int getPosition(Coordinates crd);

  void printLattice();
  void printVector();
  void saveLattice(const char* vfilename);
  void saveToPPM(const std::string& vfilename);
  void saveToPng(const std::string& filename);

private:

};


#endif
