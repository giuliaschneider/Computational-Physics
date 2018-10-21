#include "csd.hpp"
#include "Fractal.hpp"
#include "percolationlattice.hpp"
#include "squarelattice.hpp"

#include <iostream>
#include <ctime>


using namespace std;

int main(){

  /*
  Task
  */
  srand(time(0));
  double p = 0.592746;
  int N = 1000;

  csd distribution(N,p);
  squarelattice *plat = distribution.find_largestCluster();

  Fractal fractal(plat);

  fractal.SandBox();
  fractal.BoxCountingMethod();


  return 0;
}
