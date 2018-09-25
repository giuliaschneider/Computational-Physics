#include "crng.hpp"
#include "circle.hpp"
#include "stats.hpp"
#include "savedata.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>


using namespace std;



int main(){

  /*
  Task 1
  */
  int n = 2000;
  int p1 = 31;
  int p2 = 2147483647;
  int c1 = 3;
  int c2 = 16807;
  int seed = 22;
  char filename[160];


  sprintf(filename, "results/task1_p%d_c%d.txt", p1, c1);
  crng crng1(p1,c1,seed);
  //crng1.saveSequence(n, filename);

  sprintf(filename, "results/task1_p%d_c%d.txt", p2, c2);
  crng crng2(p2,c2,seed);
  //crng2.saveSequence(n, filename);


  /*
  Task 2
  */
  sprintf(filename, "results/task2.txt");
  uniform_circle(1000, filename);


  /*
  Task 3
  */
  const int n1 = 30;
  const int n2 = 3000;
  int k1 = 5;
  int k2 = 51;
  double chi2;

  int* rdn_array1 = crng1.getSequence(n1);
  chi2 = calculateChi2(rdn_array1, n1, k1, (long int) p1);
  cout << "Basic RNG" << ", n = " << n1 ;
  cout << ", Chi2 = " << chi2 << endl;

  int* rdn_array2 = crng2.getSequence(n1);
  chi2 = calculateChi2(rdn_array2, n1, k1, (long int) p2);
  cout << "Park and Miller RNG" << ", n = " << n1 ;
  cout << ", Chi2 = " << chi2 << endl;

  int* rdn_array2b = crng2.getSequence(n2);;
  chi2 = calculateChi2(rdn_array2b, n2, k2, (long int) p2);
  cout << "Park and Miller RNG" << ", n = " << n2 ;
  cout << ", Chi2 = " << chi2 << endl;

  int* rdn_array3 = new int[n1]();
  int* rdn_array3b = new int[n2]();
  double* rdn_array4 = new double[n1]();
  double* rdn_array4b = new double[n2]();

  for(int i=0;i<n1;i++){
    rdn_array3[i] = rand();
    rdn_array4[i] = drand48();
  }


  for(int i=0;i<n2;i++){
    rdn_array3b[i] = rand();
    rdn_array4b[i] = drand48();
  }


  chi2 = calculateChi2(rdn_array3, n1, k1, (long int) RAND_MAX);
  cout << "rand()" << ", n = " << n1 ;
  cout << ", Chi2 = " << chi2 << endl;

  chi2 = calculateChi2(rdn_array3b, n2, k2, (long int) RAND_MAX);
  cout << "rand()" << ", n = " << n2 ;
  cout << ", Chi2 = " << chi2 << endl;

  chi2 = calculateChi2(rdn_array4, n1, k1, (long int) 1);
  cout << "drand48()" << ", n = " << n1 ;
  cout << ", Chi2 = " << chi2 << endl;

  chi2 = calculateChi2(rdn_array4b, n2, k2, (long int) 1);
  cout << "drand48()" << ", n = " << n2 ;
  cout << ", Chi2 = " << chi2 << endl;

  delete[] rdn_array3;
  delete[] rdn_array3b;
  delete[] rdn_array4;
  delete[] rdn_array4b;


  return 0;
}
