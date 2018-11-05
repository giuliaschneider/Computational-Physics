#include <iostream>
#include "Randomwalk.hpp"
#include "savedata.hpp"



using namespace std;



int main(){

  srand(time( NULL ));

  int N = 500;
  int M = 1000;

  //Randomwalk randomwalk(N,M);
  Randomwalk randomwalk(N, M, false, true);

  //cout << "Done" << endl;



  return 0;
}
