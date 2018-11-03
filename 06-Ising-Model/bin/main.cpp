#include <iostream>
#include "Ising.hpp"
#include "savedata.h"



using namespace std;



int main(){
  int L  = 100;
  double T = 0.2;
  double J = 1;
  int nSweeps = 1000;

  srand(time( NULL ));
  Ising ising(L, T, J, nSweeps);
  ising.systemRelaxation();
  ising.averageM();


  return 0;
}
