#include "dla.hpp"
#include <iostream>



using namespace std;


int main(){

  srand(time( NULL ));
  int n  = 1000000;

  dla randomwalk(n);
  randomwalk.dlaSimulation();

  return 0;
}
