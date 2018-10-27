#include <iostream>
#include "Spheres.hpp"
#include "savedata.h"



using namespace std;


double mc_spheres(int M, int n, int R, int L){
  /**
  * calculates the average particle distance using monte carlo integration
  * returns the mean distance averaged over all configurations
  * @param M: number of configurations
  * @param n: number of spheres
  * @param R: sphere radius
  * @param L: cube size
  */
  Spheres inbox(n,R,L);
  double I = 0;

  // iterate over configurations
  for(int i=0;i<M;i++){
    inbox.createSpheres();
    double dmean = inbox.get_dmean();
    I += dmean;
  }
  double mean = I/M;
  return mean;
}

void vary_m(int n, int R, int L){
  /**
  * calculates the average particle distance using monte carlo integration
  * for a different number of configurations
  * @param n: number of spheres
  * @param R: sphere radius
  * @param L: cube size
  */

  // initalize variables
  int Mmax = 100000;
  int nConfigurations = 1000;
  int mStep = int(Mmax/nConfigurations);
  int m = 0;
  int* M = new int[nConfigurations];
  double* Im = new double[nConfigurations];

  // iterate through n configurations
  for(int i=0; i<nConfigurations; i++){
    m += mStep;
    M[i] = m;
    Im[i] = mc_spheres(m, n, R, L);
  }

  // save to text
  char filename[160];
  sprintf(filename,"results/mc_experiments_Mmax%d_n%d_L%d.txt",Mmax,n,L);
  cout << filename << endl;
  save_to_text(M,Im,nConfigurations,filename);
  delete[] M;
  delete[] Im;
}

void vary_n(){
  /**
  * calculates the average particle distance using monte carlo integration
  * for different numbers of spheres and configurations
  * @param n: number of spheres
  * @param R: sphere radius
  * @param L: cube size
  */

  // initalize variables
  int R = 1;
  int L = 10;
  int n_array[5] = {5, 10, 20, 40, 50};
  for(int i=0;i<5;i++){
    vary_m(n_array[i],R,L);
  }
}


int main(){

  /*
  Task
  */

  srand(time( NULL ));

  vary_n();

  return 0;
}
