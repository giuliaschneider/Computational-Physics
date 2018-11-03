#include <iostream>
#include "dla.hpp"
#include "savedata.hpp"



using namespace std;



int main(){

  srand(time( NULL ));

  int n  = 100000;

  dla randomwalk(n);

  //cout << "Done" << endl;



  return 0;
}
