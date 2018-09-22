#include "crng.hpp"
#include "savedata.h"
#include <iostream>
#include <fstream>
//#include "Tests.hpp"

using namespace std;



int main(){

  /*
  Task 1
  */
  int p = 31;
  int c = 3;
  char filename[160];
  sprintf(filename, "results/task1_p%d_c%d", p, c);
  crng crng2(2000,2147483647,16807,22);
  crng2.saveSequence(filename);
  //cout << rdn_array1 << endl;

  /*
  Task 2
  */
  //uniform_circle(1000);


  /*
  Task 3
  */
  //Tests tests;
  //tests.compareRNG();

  return 0;
}
