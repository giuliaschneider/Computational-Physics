#include<iostream>
#include<fstream>

using namespace std;

// The following function prints the lattice to file "output.ppm"
void Print_lattice (int *vlat, const int &vlx, const int &vly, const int &vwidth, const int &vheight, const char* vfilename="output.ppm")
{
  int  i, j, k, l;
  int vw= vwidth/vlx, vh=vheight/vly;
  int r[10], g[10], b[10];

  r[0]= 255; g[0]= 255; b[0]= 255; //white  use 0 in your lattice if you want to color it white
  r[1]=   0; g[1]=   0; b[1]=   0; //green  use 1 in your lattice if you want to color it green
  r[2]=  98; g[2]=  62; b[2]=  39; //red
  r[3]= 126; g[3]=  80; b[3]=  51; //black
  r[4]= 145; g[4]=  84; b[4]=  54; //blue
  r[5]= 149; g[5]=  95; b[5]=  60; //blue
  r[6]= 196; g[6]= 124; b[6]=  79; //blue
  r[7]= 220; g[7]= 139; b[7]=  89; //blue
  r[8]= 255; g[8]= 176; b[8]= 112; //blue
  r[9]= 255; g[9]= 195; b[9]= 124; //blue
  ofstream out (vfilename);

  out << "P3" << endl;
  out << vw*vlx << " " << vh*vly << endl;
  out << "255" << endl;

  for (i=0; i<vly; i++)
    for (j=0; j<vh; j++)
      for (k=0; k<vlx; k++)
      {
        for (l=0; l<vw; l++)
        { out << r[vlat[k+i*vlx]] << " " << g[vlat[k+i*vlx]] << " " << b[vlat[k+i*vlx]] << " ";
        }
      }
      out << endl;

  out.close ();
}
