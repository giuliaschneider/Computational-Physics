/**
  CS-11
  @file     stats.cpp
  @author   Giulia Schneider
  @date     24.94.2018
  *version  1.0
  @brief    Calculates the histogram and the Chi2-Value for a sequence of random numbers
*/

#include "crng.hpp"
#include "stats.hpp"
#include "savedata.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <armadillo>

using namespace std;


/**
* Calculates the histogram of data and saves the result in bins
* @param data: data input
* @param bins: histogram bins
* @param dataSize: number of data points
* @param nBins: number of bins
* @param maxValue: maximum number possible
*/
template<typename T>
void calcHistogram(T* data, int* bins, int dataSize, int nBins, long int maxValue){
  double dx = 1.0*maxValue/nBins;
  int index = 0;

  for(int i = 0; i<dataSize; i++){
    index = floor(data[i]/dx);
    bins[index]++;
  }
}



/**
* Calculates chi2
* @param data: Armadillo vector the number sequence to be tested
* @param dataSize: number of data points
* @param k: number of bins
* @param maxValue: maximum number possible
    @return the chi2-value
*/
template<typename T>
double calculateChi2(T* data, int dataSize,  int k, long int maxValue){
  double pi = 1.0/k;
  int *bins = new int[k]();
  double chi = 0.0;

  // cout << "Calc Hist" << endl;
  calcHistogram(data, bins, dataSize, k, maxValue);

  //printVector(bins, k);

  for(int i=0; i<k; i++){
    chi += pow(bins[i]-dataSize*pi,2)/(dataSize*pi);
  }

  delete[] bins;
  return chi;
}
