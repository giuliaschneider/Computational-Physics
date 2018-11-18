#include <iostream>
#include "Randomwalk.hpp"
#include "savedata.h"



using namespace std;



int main(){

  srand(time( NULL ));

  int N = 250;
  int M = 1000;
  char method[] = "selfAvoidingRandomWalk3D";

  Randomwalk randomwalk(N, M, method);


  return 0;
}
