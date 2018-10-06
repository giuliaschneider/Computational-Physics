/**
  CS-11
  @file     Forestfire.cpp
  @author   Giulia Schneider
  @date     06.10.2018
  *version  1.0
  @brief    Implementation of the burning algorithm
            and evaluation of the results
*/

#include "Forestfire.hpp"
#include "percolationlattice.hpp"
#include "savedata.h"
#include <iostream>
#include <fstream>
#include <stdio.h>


using namespace std;

Forestfire::Forestfire(int L): L(L), Forest(L){
}

void Forestfire::startFire(){
  /**
  * sets the occupied sites in the first row equal to two
  */

  Forest.setLattice(p,1);

  for(int i=0;i<L;i++){
    if(Forest.lat[i]!=0){
      Forest.lat[i] = 2;
    }
  }
  bottom_reached = false;
  burntNeighbor_thisTimeStep = true;
}

void Forestfire::burnNeighbors(int position, int t){
  /**
      @brief: checks the North, East, South, West neighbors
      and sets them to t+1 if they're occupied but not buring (marker = 1)
      @return void
  */

  neighborEast = position-1;
  neighborWest = position+1;
  neighborNorth = position-N;
  neighborSouth = position+N;
  burntNeighbor = false;

  if(position==0){
    if(Forest.lat[neighborEast]==1){
      Forest.lat[neighborEast]=t+1;
      burntNeighbor = true;
    }
    if(Forest.lat[neighborSouth]==1){
      Forest.lat[neighborSouth]=t+1;
      burntNeighbor = true;
    }
  }
  else if(position==N-1){
    if(Forest.lat[neighborWest]==1){
      Forest.lat[neighborWest]=t+1;
      burntNeighbor = true;
    }
    if(Forest.lat[neighborSouth]==1){
      Forest.lat[neighborSouth]=t+1;
      burntNeighbor = true;
    }
  }
  else if(position==N*N-N-1){
    if(Forest.lat[neighborEast]==1){
      Forest.lat[neighborEast]=t+1;
      burntNeighbor = true;
    }
    if(Forest.lat[neighborNorth]==1){
      Forest.lat[neighborNorth]=t+1;
      burntNeighbor = true;
    }
  }
  else if(position==N*N-1){
    if(Forest.lat[neighborWest]==1){
      Forest.lat[neighborWest]=t+1;
      burntNeighbor = true;
    }
    if(Forest.lat[neighborNorth]==1){
      Forest.lat[neighborNorth]=t+1;
      burntNeighbor = true;
    }
  }
  else{
    if(neighborEast%N!=N-1){//check if position is not boundary
      if(Forest.lat[neighborEast]==1){
        Forest.lat[neighborEast]=t+1;
        burntNeighbor = true;
      }
    }
    if(neighborWest%N!=0){//check if position is not boundary
      if(Forest.lat[neighborWest]==1){
        Forest.lat[neighborWest]=t+1;
        burntNeighbor = true;
      }
    }
    if(position > N-1){//check if position is not boundary
      if(Forest.lat[neighborNorth]==1){
        Forest.lat[neighborNorth]=t+1;
        burntNeighbor = true;
      }
    }
    if(position < N*N-N-1){//check if position is not boundary
      if(Forest.lat[neighborSouth]==1){
        Forest.lat[neighborSouth]=t+1;
        burntNeighbor = true;
        if(neighborSouth>N*N-N-1){bottom_reached = true;}
      }
    }
  }
}

void Forestfire::printFire(int &vlx, int &vly, const int &vwidth, const int &vheight, int &t, const char* vfilename){
  /**
      @brief: saves the image as a png-file
      @param: vlx:      number of sites in x-direction
      @param: vly:      number of sites in y-direction
      @param: vwidth:   width of output image
      @param: vheight:  height of output image
      @param: t:        current time step
      @param: filename: output filename
      @return void
  */

  int  i, j, k, l;
  int vw= vwidth/vlx, vh=vheight/vly;
  int r[5], g[5], b[5];

  r[0]= 255; g[0]= 255; b[0]= 255; //white  use 0 in your Forest.lattice if you want to color it white
  r[1]=  55; g[1]= 148; b[1]=  27; //green  use 1 in your Forest.lattice if you want to color it green
  r[2]= 255; g[2]=   0; b[2]=   0; //red
  r[3]=   0; g[3]=   0; b[3]=   0; //black
  r[4]=   0; g[4]=   0; b[4]= 255; //blue

  ofstream out (vfilename);

  out << "P3" << endl;
  out << vw*vlx << " " << vh*vly << endl;
  out << "255" << endl;

  for (i=0; i<vly; i++)
    for (j=0; j<vh; j++)
      for (k=0; k<vlx; k++)
      {
        for (l=0; l<vw; l++)
        {
          if(Forest.lat[k+i*vlx]==1)
            out << r[1] << " " << g[1] << " " << b[1] << " ";
          else if(Forest.lat[k+i*vlx]==t || Forest.lat[k+i*vlx]==t+1 )
            out << r[2] << " " << g[2] << " " << b[2] << " ";
          else if(Forest.lat[k+i*vlx]==0)
            out << r[0] << " " << g[0] << " " << b[0] << " ";
          else
            out << r[3] << " " << g[3] << " " << b[3] << " ";



          }
        }
      out << endl;
  out.close ();
}

void Forestfire::BurningMethod(bool printFigures){
  /**
      @brief: implementation of the Buring Method algorithm
      @param: vlx:      true, if the lattice should be saved as image at every time steps
      @return void
  */
  t = 2;
  startFire();
  if(printFigures){
    sprintf(filename,"../report/figures/2_task_t%02d_p%.2f.png",t,p);
    printFire(N,N,Forest.ImageWidth,Forest.ImageHeight,t,filename);
  }
  while(!bottom_reached && burntNeighbor_thisTimeStep){

    burntNeighbor_thisTimeStep = false;
    for(int i=0;i<(N*N);i++){
      if(Forest.lat[i]==t){ //Find burning trees
         burnNeighbors(i,t); //Burn neighboring trees
         if(burntNeighbor) burntNeighbor_thisTimeStep = true;
      }
    }
    t++;
    if(printFigures){
      sprintf(filename,"../report/figures/2_task_t%02d_p%.2f.png",t,p);
      printFire(N,N,Forest.ImageWidth,Forest.ImageHeight,t,filename);
    }
  }
  if(bottom_reached){shortest_path = t-1;}
  lifeTime = t;
}

void Forestfire::FireStatistics(int n_experiments){
  /**
      @brief: evaluates the probability of finding a spanning cluster, the average shortest path and life time
      @param: n_experiments: number of experiments to be reapeated for statistics
      @return void
  */
  avg_spanningCluster = 0.0;
  avg_shortest_path = 0.0;
  avg_lifeTime = 0.0;

  //Parallelize for loop
  #pragma omp parallel for
  for(int exp=0;exp<n_experiments;exp++){
    srand(exp);
    BurningMethod(false);
    if(bottom_reached) {
      avg_spanningCluster += 1.0;
      avg_shortest_path += shortest_path;
    }
    avg_lifeTime += lifeTime;
  }

  avg_shortest_path = (double)(avg_shortest_path/avg_spanningCluster);
  avg_spanningCluster = (double)(avg_spanningCluster/n_experiments);
  avg_lifeTime = (double)(avg_lifeTime/n_experiments);
}

void Forestfire::FireStatistics_different_p(int n_experiments){
  /**
      @brief: evaluates the Burning method for differend occupation probabilites p
      @param: n_experiments: number of experiments to be reapeated for statistics
      @return void
  */
  memset(vec_p_spanningCluster,0.0,sizeof(double)*size_p_array);
  memset(vec_p_shortest_path,0.0,sizeof(double)*size_p_array);
  memset(vec_p_lifeTime,0.0,sizeof(double)*size_p_array);
  for(int i=0; i < size_p_array; i++){
    p = i/100.0;
    FireStatistics(n_experiments);
    vec_p_spanningCluster[i] = avg_spanningCluster;
    vec_p_shortest_path[i] = avg_shortest_path;
    vec_p_lifeTime[i] = avg_lifeTime;
    cout << "completet p nr . " << i << endl;
  }
    sprintf(filename,"python_scripts/3a_vec_spanningCluster_N%03d.txt",N);
    save_to_text(vec_p_spanningCluster,size_p_array,filename);
    sprintf(filename,"python_scripts/3b_vec_shortest_path_N%03d.txt",N);
    save_to_text(vec_p_shortest_path,size_p_array,filename);
    sprintf(filename,"python_scripts/3c_vec_lifeTime_N%03d.txt",N);
    save_to_text(vec_p_lifeTime,size_p_array,filename);

}




Forestfire::~Forestfire(){
}
