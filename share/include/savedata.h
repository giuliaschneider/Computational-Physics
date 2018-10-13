#ifndef SAVEDATA_HPP_INCLUDED_
#define SAVEDATA_HPP_INCLUDED_


#include<iostream>
#include <iomanip>      // std::setw
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator
#include <vector>
#include<fstream>

using namespace std;


void printVector(const vector<int> &data);

template<typename T>
void printVector(const T *data, const int &size);
template<typename T>
void printVector(const T *data, const T *data2, const int &size);


void save_to_text(const vector<int> *data, const char* vfilename);

template<typename T>
void save_to_text(const T *data, const int size, const char* vfilename);


#include "savedata.tpp"
#endif
