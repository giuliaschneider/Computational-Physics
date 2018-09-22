/**
  CS-11
  @file     crng.cpp
  @author   Giulia Schneider
  @date     24.04.2018
  *version  1.0
  @brief    Generates random numbers using a congruential RNG algorithm
*/

#include "crng.hpp"
#include "savedata.h"
//#include <iostream>
//#include <math.h>
//#include <stdlib.h>
//#include <armadillo>

using namespace std;


/**
Constructor
* @param numberRNG:   number of random points
* @param p:           parameter of congruential RNG algorithm
* @param c:           parameter of congruential RNG algorithm
* @param seed:        seed
*/
crng::crng(int numberRNG, int p, int c, int seed):
  numberRNG(numberRNG), p(p), c(c), rdn(seed){
    rng_max = p;
    rdn_array = new int[numberRNG];
}

/**
Destructor
*/
crng::~crng(){
  delete[] rdn_array;
}


/**
* Calculate a random number using the congruential RNG algorithm
*/
void crng::generateNumber(){
  rdn = (c*rdn)%p;
}


/**
* Calculate a sequence of random numbers
*/
void crng::generateSequence(){
  for(int i=0;i<numberRNG;i++){
    rdn_array[i] = rdn;
    generateNumber();
  }
}

/**
* Get a sequence of random numbers
* @return: arma::vec
*/
int* crng::getSequence(){
  generateSequence();
  return rdn_array;
}

/**
* Save a sequence of random numbers to file
* @param: char* filename
* @return: arma::vec
*/
void crng::saveSequence(char* filename){
  generateSequence();
  printVector<int>(rdn_array, numberRNG);
}
