#ifndef CRNG
#define CRNG

#include <iostream>


class crng {
private:
  int numberRNG;
  unsigned long int rdn;
  unsigned long int seed;
  int c;
  int p;
  int* rdn_array;

public:
  int rng_max;

private:
  void generateNumber();
  void generateSequence(int numberRNG);

public:
  crng(int p, int c, int seed);
  ~crng();
  int* getSequence(int numberRNG);
  void saveSequence(int numberRNG, char* filename);
};



#endif
