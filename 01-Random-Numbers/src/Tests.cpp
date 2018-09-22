/**
  CS-11
  @file     Tests.cpp
  @author   Giulia Schneider
  @date     24.94.2018
  *version  1.0
  @brief    Calculates the histogram and the Chi2-Value for a sequence of random numbers
*/

#include "crng.hpp"
#include "Tests.hpp"
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <armadillo>

using namespace std;


/**
    @brief: counts the number of points within k evenly spaced bins
    @param rdn_array: Armadillo vector the number sequence to be tested
    @param k: number of bins
    @param rng_max: maximum number possible
    @return armadillo vector with the number of points in each bin
*/
arma::vec Tests::countInterval(arma::vec &rdn_array, int k, long int rng_max){
  double dx = 1.0*rng_max/k;
  arma::vec countInt( k );
  int index = 0;

  for(int i = 0; i<rdn_array.n_elem; i++){
    index = floor(rdn_array(i)/dx);
    countInt(index)++;
  }
  return countInt;
}

/**
    @brief: prints the number of points in each bin
    @param rdn_array: Armadillo vector the number sequence to be tested
    @param k: number of bins
    @param rng_max: maximum number possible
    @return armadillo vector with the number of points in each bin
*/
void Tests::getHistogram(arma::vec &rdn_array, int k, long int rng_max){
  arma::vec bins = countInterval(rdn_array, k, rng_max);
  cout << bins << endl;
}

/**
    @brief: calculates the chi2 value
    @param rdn_array: Armadillo vector the number sequence to be tested
    @param k: number of bins
    @param rng_max: maximum number possible
    @return the chi2-value
*/
double Tests::calculateChi2(arma::vec &rdn_array, int k, long int rng_max){
  double pi = 1.0/k;
  arma::vec countInt = countInterval(rdn_array, k, rng_max);
  double chi = 0.0;

  for(int i = 0; i<k;i++){
    chi = chi +  pow(countInt(i)-rdn_array.n_elem*pi,2)/(rdn_array.n_elem*pi);
  }
  return chi;
}

/**
    @brief: prints the chi2 value
    @param rdn_array: Armadillo vector the number sequence to be tested
    @param k: number of bins
    @param rng_max: maximum number possible
    @return the chi2-value
*/
void Tests::getChi2(arma::vec &rdn_array, int k, long int rng_max){
  double chi2 = calculateChi2(rdn_array, k, rng_max);
  cout << chi2 << endl;
}



/**
    @brief: tests different RNGs and saves the results to a .tex file
    @return void
*/
void Tests::compareRNG(){
  int k1 = 5;
  int num_rn = 30;
  int k2 = 51;
  int num_rn2 = 3000;
  crng crng1(num_rn,31,3,22);
  arma::vec rdn_array1 = crng1.getSequence();
  double chi2_1 = calculateChi2(rdn_array1, k1, 31);
  crng crng2(num_rn,2147483647,16807,22);
  arma::vec rdn_array2 = crng2.getSequence();
  double chi2_2 = calculateChi2(rdn_array2, k1, 2147483647);

  crng crng2b(num_rn2,2147483647,16807,22);
  arma::vec rdn_array2b = crng2b.getSequence();
  double chi2_2b = calculateChi2(rdn_array2b, k2, 2147483647);

  arma::vec rdn_array3(num_rn);
  arma::vec rdn_array4(num_rn);
  arma::vec rdn_array3b(num_rn2);
  arma::vec rdn_array4b(num_rn2);
  for(int i=0;i<rdn_array3.n_elem;i++){
    rdn_array3(i) = rand();
    rdn_array4(i) = drand48();
  }
  double chi2_3 = calculateChi2(rdn_array3, k1, RAND_MAX);
  double chi2_4 = calculateChi2(rdn_array4, k1, 1);
  for(int i=0;i<rdn_array3b.n_elem;i++){
    rdn_array3b(i) = rand();
    rdn_array4b(i) = drand48();
  }
  double chi2_3b = calculateChi2(rdn_array3b, k2, RAND_MAX);
  double chi2_4b = calculateChi2(rdn_array4b, k2, 1);




  ofstream outFile;
  cout << outFile << endl;
  string outputFileName = "../../report/tables/3.tex";
  outFile.open(outputFileName);
  if(outFile.is_open()){
    outFile.setf(ios::fixed, ios::floatfield);
    outFile.precision(2);
    outFile << "/begin{table}[htp]" << endl;
    outFile << "/caption{default}" << endl;
    outFile << "/begin{center}" << endl;
    outFile << "/begin{tabular}{l|rrrr}" << endl;
    outFile << "/toprule" << endl;
    outFile << "RNG \t \t \t" << "&Number of RN \t"<< "&Number of Bins \t" << "&$/chi^2_{Table}$ \t "<<"&$chi^2$ " << "//" << endl;
    outFile << " \t \t \t " << "&$n$ \t \t " << "&$k$ \t\t " "&$0.05 < p < 0.95$ \t " << "//" << endl;
    outFile << "/midrule" << endl;
    outFile << "Basic RNG \t \t &"  <<num_rn  << " \t\t& " << k1 << "\t\t" << "&[0.1026, 5.991] \t&" << chi2_1<< "//" << endl;
    outFile << "Park and Miller RNG \t&" << num_rn << "\t\t&" << k1 << "\t\t" << "&[0.1026, 5.991] \t&" <<  chi2_2 << "//" << endl;
    outFile << "Park and Miller RNG \t&" << num_rn2 << "\t\t&" << k2 << "\t\t" << "&[0.34.76, 67.50] \t&"<<  chi2_2b<< "//" << endl;
    outFile << "rand() \t\t\t&" << num_rn << "\t\t&" << k1 << "\t\t" << "&[0.1026, 5.991] \t&" << chi2_3 << "//" << endl;
    outFile << "rand() \t\t\t&" << num_rn2 << "\t\t&" << k2 << "\t\t" << "&[0.3476, 67.50] \t&" << chi2_3b << "//" << endl;
    outFile << "drand48()\t \t&" << num_rn << "\t\t&" << k1 << "\t\t" << "&[0.1026, 5.991] \t&" << chi2_4 << "//" <<endl;
    outFile << "drand48()\t\t&" << num_rn2 << "\t\t&" << k2 << "\t\t" << "&[0.3476, 67.50] \t&" << chi2_4b<< "//" << endl;
    outFile << "/bottomrule" << endl;
    outFile << "/end{tabular}" << endl;
    outFile << "/end{center}" << endl;
    outFile << "/label{default}" << endl;
    outFile << "/end{table}" << endl;





    outFile.close();
  }
  else {
    cout << "Could not create file: " << outputFileName << endl;
  }

}
