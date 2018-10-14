#include "savedata.h"
#include<iostream>
#include <iomanip>      // std::setw
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator
#include <vector>
#include<fstream>



void printVector(const vector<int> &data){
    /* Print data vector to console */
    copy(data.begin(), data.end(), ostream_iterator<int>(cout, "\n"));
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


void save_to_text(const vector<int> &data1, const vector<int> &data2, const char* vfilename){
    ofstream outFile;
    outFile.open(vfilename);
    int size = data1.size();

    if(outFile.is_open()){
      for(int i = 0; i<size; i++){
        outFile << data1[i] << "\t" << data2[i] << endl;
      }
        outFile.close();
    }
    else {
        cout << "Could not create file: " << vfilename << endl;
    }
}
