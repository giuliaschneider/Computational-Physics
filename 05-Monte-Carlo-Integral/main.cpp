#include <iostream>
#include "Spheres.hpp"
#include "savedata.hpp"



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
  return I/M;
}

void run_mcexperiments(int n, int R, int L){
  /**
  * calculates the average particle distance using monte carlo integration
  * returns the mean distance averaged over all configurations
  * @param M: number of configurations
  * @param n: number of spheres
  * @param R: sphere radius
  * @param L: cube size
  */
  cout << "M  \tdmean" << endl;
  int Mmax = 300000;
  int Nmax = 1000;
  int m = 200;
  int* M = new int[Nmax];
  double* Im = new double[Nmax];
  for(int i=0; i<Nmax; i++){
    cout << "M = " << m << endl;
    M[i] = m;
    Im[i] = mc(m, n, R, L);
    m += Mmax/Nmax;
  }
  char filename[160];
  sprintf(filename,"python_scripts/mc_experiments_Mmax%d_n%d_L%d.txt",Mmax,n,L);
  save::save_to_text(M,Im,Nmax,filename);
  delete[] M;
  delete[] Im;
}

void vary_n(){
  int R = 1;
  int L = 10;
  int n_array[5] = {5, 10, 20, 40, 50};
  for(int i=0;i<5;i++){
    cout << n_array[i] << endl;
    run_mcexperiments(n_array[i],R,L);
  }
}


int main(){
  int n  = 50;
  int R = 1;
  int L = 10;
  srand(time( NULL ));
  //mc(1,n,R,L);
  run_mcexperiments(n, R, L);
  //vary_n();

  return 0;
}
