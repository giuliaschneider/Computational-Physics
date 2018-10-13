
#ifndef FRACTAL
#define FRACTAL


#include "squarelattice.hpp"


class Fractal{
public:
  squarelattice *lat;
private:
    int L;
    char filename[160];
public:
  Fractal(squarelattice* arr);
  ~Fractal();
  int findOccupiedCenterPosition();
  void SandBox();
  void BoxCountingMethod();
private:

};

#endif
