#ifndef CRNG
#define CRNG

#include <iostream>


class crng {
private:
  int numberRNG;
  unsigned long int rdn;
  int c;
  int p;
  int* rdn_array;

public:
  int rng_max;

private:
  void generateNumber();
  void generateSequence();

public:
  crng(int numberRNG, int p, int c, int seed);
  ~crng();
  int* getSequence();
  void saveSequence(char* filename);
};



#endif
