#include "percolationlattice.hpp"
#include "Forestfire.hpp"
#include <iostream>


using namespace std;

int main(){

  /*
  Task 1
  */
  percolationlattice lat(100, 0.5);
  lat.setLattice_differentProbabilities();

  /*
  Task 2
  */
  Forestfire forestfire(50, 0.7);
  forestfire.BurningMethod(true);

  /*
  Task 3
  */
  forestfire.stats_differentProbabilities(1000);

  return 0;
}
