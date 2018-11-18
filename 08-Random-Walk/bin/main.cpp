#include <iostream>
#include <string>
#include "Randomwalk.hpp"
#include "savedata.h"



using namespace std;



int main(){

  srand(time( NULL ));

  int N = 500;
  int M = 1000;
  char method[] = "randomwalk2D";

  Randomwalk randomwalk(N, M, method);


  return 0;
}
