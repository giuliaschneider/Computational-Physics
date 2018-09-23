#ifndef SAVEDATA_HPP_INCLUDED_
#define SAVEDATA_HPP_INCLUDED_


#include<iostream>
#include <iomanip>      // std::setw
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator
#include <vector>
#include<fstream>

using namespace std;




void printVector(const vector<int> *data);

template<typename T>
void printVector(const T *data, const int &size);
template<typename T>
void printVector(const T *data, const T *data2, const int &size);


void printPositions(const double *xdata, const double *ydata, const double *zdata, const int &size);

void printLattice(const int *data, const int &N);

void save_to_text(const vector<int> *data, const char* vfilename);


template<typename T>
void save_to_text(const T *data, const int size, const char* vfilename);
void save_to_text(const char *header1, const char *header2, const int *data1, const int *data2, const int size, const char* vfilename);

void save_to_text(const char *header1, const char *header2, const char *header3,  const int *data1, const double *data2, const double * data3, const int size, const char* vfilename);

#include "savedata.tpp"
#endif
