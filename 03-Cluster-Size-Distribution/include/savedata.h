#include<iostream>
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator
#include <vector>
#include<fstream>

using namespace std;

void printVector(const vector<int> *data){
    /* Print data vector to console */
    copy(data->begin(), data->end(), ostream_iterator<int>(cout, "\n"));
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


void save_to_text(const double *data, const int size, const char* vfilename){
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
