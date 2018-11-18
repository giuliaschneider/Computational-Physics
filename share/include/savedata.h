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
void save_to_text(const vector<int> &data1, const vector<int> &data2, const char* vfilename);


template<typename T>
void save_to_text(const T *data, const int size, const char* vfilename);
template<typename T, typename U>
void save_to_text(const T *data1, const U *data2, const int size, const char* vfilename);
template<typename T, typename U>
void save_to_text(const char* header1, const char* header2,
  const T *data1, const U *data2, const int size, const char* vfilename);
template<typename T, typename U, typename V>
void save_to_text(const char* header1, const char* header2, const char* header3,
  const T *data1, const U *data2, const V *data3, const int size, const char* vfilename);


#include "savedata.tpp"
#endif
