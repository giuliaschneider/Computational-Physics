#ifndef SAVEDATA_HPP_INCLUDED_
#define SAVEDATA_HPP_INCLUDED_


#include<iostream>
#include <iomanip>      // std::setw
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator
#include <vector>
#include<fstream>

using namespace std;


namespace save {

void printVector(const vector<int> *data);

void printVector(const int *data, const int &size);
void printVector(const double *data, const int &size);

void printPositions(const double *xdata, const double *ydata, const double *zdata, const int &size);

void printLattice(const int *data, const int &N);

void save_to_text(const vector<int> *data, const char* vfilename);

void save_to_text(const double *data, const int size, const char* vfilename);
void save_to_text(const int *data1, const double *data2, const int size, const char* vfilename);

}
#endif
