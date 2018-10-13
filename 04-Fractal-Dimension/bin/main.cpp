#include "csd.hpp"
#include "Fractal.hpp"
#include "percolationlattice.hpp"
#include "squarelattice.hpp"

#include <iostream>
#include <iomanip>      // std::setw



using namespace std;

int main(){

  /*
  Task 1
  */
  double p = 0.592746;
  int N = 6;

  csd distribution(N,0.6);
  squarelattice *plat = distribution.find_largestCluster();
  plat->printLattice();

  Fractal fractal(plat);

  fractal.SandBox();

  /*
  fractal.BoxCountingMethod();

*/




  /*
  Task 2
  */





  return 0;
}
