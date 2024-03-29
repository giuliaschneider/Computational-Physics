#ifndef SAVEDATA_TPP
#define SAVEDATA_TPP


#include "savedata.h"
#include<iostream>
#include <iomanip>      // std::setw
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator
#include <vector>
#include<fstream>

using namespace std;





template <class T>
void printVector(const T *data, const int &size){
    /* Print data array to console */
    for(int i=0;i<size;i++){
        cout << data[i] << endl;
    }
}


template <class T>
void printVector(const T *data, const T *data2, const int &size){
    /* Print data array to console */
    for(int i=0;i<size;i++){
        cout << data[i] << ',' << data2[i] << endl;
    }
}


template <class T>
void save_to_text(const T *data, const int size, const char* vfilename){
  ofstream outFile;
  outFile.open(vfilename);

  if(outFile.is_open()){
    outFile.setf(ios::fixed, ios::floatfield);
    outFile.precision(2);
    for(int i=0; i < size; i++)
    outFile << data[i] << endl;
    outFile.close();
  }
  else {
    cout << "Could not create file: " << vfilename << endl;
  }
}

template<typename T, typename U>
void save_to_text(const T *data1, const U *data2, const int size, const char* vfilename){
  ofstream outFile;
  outFile.open(vfilename);

  if(outFile.is_open()){
    outFile.setf(ios::fixed, ios::floatfield);
    outFile.precision(13);
    for(int i=0; i < size; i++){
      outFile << data1[i] << ", " << data2[i] << endl;
    }
    outFile.close();
  }
  else {
    cout << "Could not create file: " << vfilename << endl;
  }
}

template<typename T, typename U>
void save_to_text(const char* header1, const char* header2,
const T *data1, const U *data2, const int size, const char* vfilename){
  ofstream outFile;
  outFile.open(vfilename);

  if(outFile.is_open()){
    outFile.setf(ios::fixed, ios::floatfield);
    outFile.precision(13);
    outFile << header1 << ", " << header2 << endl;
    for(int i=0; i < size; i++){
      outFile << data1[i] << ", " << data2[i] << endl;
    }
    outFile.close();
  }
  else {
    cout << "Could not create file: " << vfilename << endl;
  }
}

template<typename T, typename U, typename V>
void save_to_text(const char* header1, const char* header2, const char* header3,
const T *data1, const U *data2, const V *data3, const int size, const char* vfilename){
  ofstream outFile;
  outFile.open(vfilename);

  if(outFile.is_open()){
    outFile.setf(ios::fixed, ios::floatfield);
    outFile.precision(13);
    outFile << header1 << ", " << header2 << ", " << header3 << endl;
    for(int i=0; i < size; i++){
      outFile << data1[i] << ", " << data2[i] << ", " << data3[i] << endl;
    }
    outFile.close();
  }
  else {
    cout << "Could not create file: " << vfilename << endl;
  }
}



#endif
