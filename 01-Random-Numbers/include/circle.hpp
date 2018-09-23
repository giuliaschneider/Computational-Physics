#include <iostream>
#include <fstream>

#include <math.h>
#include <stdlib.h>



/**
* Calculates random points homogeneously distributed within a circle
* @param numberRNG:   number of random points
* @return void
*/
void uniform_circle(int numberRNG, char* filename){
  int R = 1;
  double phi = 0.0;
  double r = 0.0;

  std::ofstream outFile;
  outFile.open(filename);

  if(outFile.is_open()){
    outFile.setf(std::ios::fixed, std::ios::floatfield);
    outFile.precision(2);
    for(int i=0;i<numberRNG;i++){
      phi = (2*M_PI*rand())/RAND_MAX;
      r = R*sqrt((1.0*rand())/RAND_MAX);
      outFile << r*cos(phi) << '\t' << r*sin(phi) << std::endl;
    }
    outFile.close();
  }
  else {
    std::cout << "Could not create file: " << filename << std::endl;
  }
}
