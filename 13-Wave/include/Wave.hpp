
#ifndef WAVE
#define WAVE


namespace comphys{

class Wave{
private:
  double x0;
  double xend;
  int h;
  double dx;
  double t0;
  double tend;
  double nSteps;
  double dt;
  double c;
  double c1;
  double c2;
  double b;

  double xi = 0;
  double* u_now;
  double* u_tt;
  double* temp;
  double* pOriginal;

  char filename[160];

private:
  void setIC();
  void calcWave();
public:
  Wave(double a, double b, int h, double t0, double tend, double dt, double c);
  ~Wave();
};

}

#endif
