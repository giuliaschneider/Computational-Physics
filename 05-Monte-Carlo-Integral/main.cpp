#include <iostream>
#include "Spheres.hpp"
#include "savedata.hpp"



using namespace std;


double mc(int M, int n, int R, int L){
  /**
      @brief: calculates the avereage particle distance using monte carlo integration
      @param: 
      @return double average particle distance
  */

  Spheres inbox(n,R,L);

  double I = 0;

  for(int i=0;i<M;i++){
    //cout << "k = " << i << endl;
    inbox.createSpheres();
    double dmean = inbox.get_dmean();
    I = I + dmean;
  }
  I = I/M;
  return I;
  //cout << "I = " << I << endl;
}

void run_mcexperiments(int n, int R, int L){
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
