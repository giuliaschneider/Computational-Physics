/**
  CS-11
  @file     crng.cpp
  @author   Giulia Schneider
  @date     24.04.2018
  *version  1.0
  @brief    Generates random numbers using a congruential RNG algorithm
*/

#include "crng.hpp"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <armadillo>

using namespace std;


/**
    @brief: prints random points homogeneously distributed within a circle
    @param numberRNG:   number of random points
    @return void
*/
void uniform_circle(int numberRNG){
  int R = 1;
  double phi = 0.0;
  double r = 0.0;
  for(int i=0;i<numberRNG;i++){
    phi = (2*M_PI*rand())/RAND_MAX;
    r = R*sqrt((1.0*rand())/RAND_MAX);
    cout << r*cos(phi) << '\t' << r*sin(phi) << endl;
  }
}


/**
    @brief: Constructs a congruential RNG
    @param numberRNG:   number of random points
    @param p:           parameter of congruential RNG
    @param c:           parameter of congruential RNG
    @param seed:        seeds
*/
crng::crng(int numberRNG, int p, int c, int seed):
  numberRNG(numberRNG), p(p), c(c), rdn(seed){
    rng_max = p;
    rdn_array.set_size( numberRNG );
  }

  /**
      @brief:     calculates a random number using the congruential RNG algorithm
      @param rdn: current random number
      @return:    return the next random number
  */
int crng::generateNumber(unsigned long int rdn){
  return rdn = (c*rdn)%p;
}

/**
    @brief: calculates a sequence on random numbers
    @return: void
*/
void crng::generateSequence(){
  for(int i=0;i<numberRNG;i++){
    rdn_array(i) = rdn;
    rdn = generateNumber(rdn);
  }
}

/**
    @brief: returns the sequence of random numbers
    @return: arma::vec
*/
arma::vec crng::getSequence(){
  generateSequence();
  return rdn_array;
}
