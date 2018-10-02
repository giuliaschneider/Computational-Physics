
#ifndef PERCOLATION
#define PERCOLATION

class Percolation{
public:
  const int ImageWidth;
  const int ImageHeight;
private:
  double p;
  double z;
  int N;
  char filename[160];
  char filename_png[160];
public:
  int *lat;
public:
  Percolation(int N);
  Percolation(int N, double p);
  ~Percolation();
  void createLattice(double p,int color);
  void calc_different_p();
  void saveFigure(char *filename);
};

#endif
