#include "savedata.h"
#include<iostream>
#include <iomanip>      // std::setw
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator
#include <vector>
#include<fstream>



void printVector(const vector<int> *data){
    /* Print data vector to console */
    copy(data->begin(), data->end(), ostream_iterator<int>(cout, "\n"));
}

void printPositions(const double *xdata, const double *ydata, const double *zdata, const int &size){
    /* Print data array to console */
    for(int i=0;i<size;i++){
        cout << xdata[i] << "\t" << ydata[i] << "\t" << zdata[i]<< endl;
    }
}

void printLattice(const int *data, const int &N){
    cout << "Printing" << endl;
    for(int i=0;i<(N*N);i++){
        cout <<  setw(2);
        if(i%N==N-1){
            cout << data[i] << "|" << endl;
        }
        else{

            cout <<  data[i] << "|"<< flush;
        }
    }
}

void save_to_text(const vector<int> *data, const char* vfilename){
    ofstream outFile;
    outFile.open(vfilename);

    if(outFile.is_open()){
        copy(data->begin(), data->end(), ostream_iterator<int>(outFile, "\n"));
        outFile.close();
    }
    else {
        cout << "Could not create file: " << vfilename << endl;
    }
}

void save_to_text(const char *header1, const char *header2, const int *data1, const int *data2, const int size, const char* vfilename){
  ofstream outFile;
  outFile.open(vfilename);

  if(outFile.is_open()){
    outFile.setf(ios::fixed, ios::floatfield);
    outFile.precision(6);
    for(int i=0; i < size; i++)
    outFile << data1[i] << ", " << data2[i]  << endl;
    outFile.close();
  }
  else {
    cout << "Could not create file: " << vfilename << endl;
  }
}


void save_to_text(const char *header1, const char *header2, const char *header3, const int *data1, const double *data2, const double * data3, const int size, const char* vfilename){
  ofstream outFile;
  outFile.open(vfilename);

  if(outFile.is_open()){
    outFile.setf(ios::fixed, ios::floatfield);
    outFile.precision(6);
    outFile << header1 << ", " << header2 << ", " << header3 << endl;
    for(int i=0; i < size; i++)
    outFile << data1[i] << ", " << data2[i] << ", " << data3[i] << endl;
    outFile.close();
  }
  else {
    cout << "Could not create file: " << vfilename << endl;
  }
}
