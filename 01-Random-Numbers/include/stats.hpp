
#ifndef STATS
#define STATS


template<typename T>
void calcHistogram(T* data, int* bins, int dataSize, int nBins, long int maxValue);

template<typename T>
double calculateChi2(T* data, int dataSize,  int k, long int maxValue);


#include "stats.tpp"

#endif
