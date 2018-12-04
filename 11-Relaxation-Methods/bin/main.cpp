#include "poisson2d.hpp"
#include <iostream>


using namespace std;

int main(){

  /*
  Task 1
  */
  int n_charges = 1;
  //double x0[3] = {0.2, 0.6, 0.75};
  //double y0[3] = {0.8, 0.1, 0.75};
  double x0[1] = {0.75};
  double y0[1] = {0.75};
  string method = "Jacobi";
  comphys::poisson2d jabobi(50, n_charges, x0, y0, 0.00001,method);
  jabobi.calc_Poisson();

  method = "Gauss Seidel";
  comphys::poisson2d gauss(50, n_charges, x0, y0, 0.00001,method);
  gauss.calc_Poisson();

  /*
  Task 2
  */


  /*
  Task 3
  */


  return 0;
}
