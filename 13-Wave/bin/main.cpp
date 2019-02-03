#include "Wave.hpp"
#include <iostream>


using namespace std;

int main(){

  /*
  Task 1
  */
  double a = 0;
  double b = 20;
  int h = 200;
  double t0 = 0.0;
  double tend = 10.0;
  double dt = 0.05;
  double c = 2.0;
  comphys::Wave wave(a, b, h, t0, tend, dt, c);


  return 0;
}
