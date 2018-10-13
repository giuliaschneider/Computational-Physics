#include<iostream>
#include<fstream>

using namespace std;

// The following function prints the lattice to file "output.ppm"
void Print_lattice (const int *vlat, const int &vlx, const int &vly, const int &vwidth, const int &vheight, const char* vfilename="output.ppm")
{
  int  i, j, k, l;
  int vw= vwidth/vlx, vh=vheight/vly;
  int r[5], g[5], b[5];

  r[0]= 255; g[0]= 255; b[0]= 255; //white  use 0 in your lattice if you want to color it white
  r[1]=  55; g[1]= 148; b[1]=  27; //green  use 1 in your lattice if you want to color it green
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
        { out << r[vlat[k+i*vlx]] << " " << g[vlat[k+i*vlx]] << " " << b[vlat[k+i*vlx]] << " ";
        }
      }
      out << endl;

  out.close ();
  char cmd[160],filename_png[160];
  int len_filename = strlen(vfilename)-2;
  sprintf(filename_png, "%.*sng", len_filename , vfilename);
  cout << filename_png << endl;
//  filename_png[strlen(filename_png)-2] = "n";
//  filename_png[strlen(filename_png)-1] = "g";

  //sprintf(filename_png,"../report/figures/task1_%03f.png",1);
  sprintf(cmd,"sips -s format png %s --out %s; rm -f %s",vfilename,filename_png,vfilename); // rm automatically deletes the ppm-file to save memory (removes test002.ppm)
  system(cmd);
}
