#include "csd.hpp"
#include "Fractal.hpp"
#include "percolationlattice.hpp"
#include "squarelattice.hpp"

#include <iostream>
#include <iomanip>      // std::setw
#include <ctime>


using namespace std;

int main(){

  /*
  Task 1
  */

  srand(time(0));
  double p = 0.592746;
  int N = 5000;

  csd distribution(N,0.6);
  squarelattice *plat = distribution.find_largestCluster();

  Fractal fractal(plat);

  fractal.SandBox();
  fractal.BoxCountingMethod();




  return 0;
}
