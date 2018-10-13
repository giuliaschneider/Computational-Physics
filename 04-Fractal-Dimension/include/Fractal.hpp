
#ifndef FRACTAL
#define FRACTAL


class Fractal{
public:
  const int ImageWidth;
  const int ImageHeight;
public:
  int *lat;
private:
    int N;
    char filename[160];
public:
  Fractal(int N);
  ~Fractal();
  void setLattice(int* arr);
  void SandBox();
  void BoxCountingMethod();
private:

};

#endif
