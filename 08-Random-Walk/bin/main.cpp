#include <iostream>
#include "Randomwalk.hpp"
#include "savedata.h"



using namespace std;



int main(){

  srand(time( NULL ));

  int N = 500;
  int M = 1000;

  Randomwalk randomwalk(N, M, false, true);


  return 0;
}
