
#ifndef SPHERES
#define SPHERES


class Spheres{
private:
  int n;
  double L;
  double R;
public:
  double* xpositions;
  double* ypositions;
  double* zpositions;
  double* d;
  double dmean;
  char filename[160];
public:
  Spheres(int n, double R);
  Spheres(int n, double R, double L);
  ~Spheres();
  void createSpheres();
  void calc_dmean();
  double get_dmean();
private:
  void getDistances();
  int calcDistance(int x, int y, int z, int positon);

};


#endif
