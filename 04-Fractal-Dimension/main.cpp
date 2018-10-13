#include "Percolation.hpp"
#include "Fractal.hpp"
#include <iostream>
#include <iomanip>      // std::setw



using namespace std;

int main(){

  /*
  Task 1
  */
  double p = 0.592746;
  int N = 10000;
  Percolation percolation(N,p);
  cout << "Created Percolation Object" << endl;
  percolation.find_largestCluster();
  cout << "Found Largest Cluster " << endl;

  int *plat = percolation.getLattice();

  Fractal fractal(N);
  fractal.setLattice(plat);
  fractal.SandBox();
  fractal.BoxCountingMethod();




  /*
  Task 2
  */





  return 0;
}
