#include <iostream>
#include "Ising.hpp"
#include "savedata.hpp"



using namespace std;



int main(){
  int L  = 1024;
  double T = 0.2;
  double J = 1.0;
  int nSweeps = 1000;

  srand(time( NULL ));
  Ising(L, T, J, nSweeps);

  return 0;
}
