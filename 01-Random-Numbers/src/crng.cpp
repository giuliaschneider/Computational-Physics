/**
  CS-11
  @file     crng.cpp
  @author   Giulia Schneider
  @date     25.09.2018
  @version  1.0
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
crng::crng(int p, int c, int seed):
  p(p), c(c), seed(seed){
    rng_max = p;
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
void crng::generateSequence(int numberRNG){
  rdn_array = new int[numberRNG];
  rdn = seed;
  for(int i=0;i<numberRNG;i++){
    rdn_array[i] = rdn;
    generateNumber();
  }
}

/**
* Get a sequence of random numbers
* @return: arma::vec
*/
int* crng::getSequence(int numberRNG){
  generateSequence(numberRNG);
  return rdn_array;
}

/**
* Save a sequence of random numbers to file
* @param: char* filename
* @return: arma::vec
*/
void crng::saveSequence(int numberRNG, char* filename){
  generateSequence(numberRNG);
  save_to_text<int>(rdn_array, numberRNG, filename);
}
