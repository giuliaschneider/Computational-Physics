#include "Percolation.hpp"
//#include "Forestfire.hpp"
#include <iostream>


using namespace std;

int main(){

  /*
  Task 1
  */
  Percolation percolation(100, 0.5);
  percolation.setLattice(0.5, 1);
  percolation.saveFigure("test.png");
  //percolation.calc_different_p();

  /*
  Task 2
  */

  /*
  Task 3
  */
  //Forestfire forestfire(20);
  //forestfire.FireStatistics_different_p(1000);


  return 0;
}
