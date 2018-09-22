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

#endif
