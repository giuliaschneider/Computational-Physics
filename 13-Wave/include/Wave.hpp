
#ifndef WAVE
#define WAVE

#include <armadillo>

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
  arma::vec x;
  //arma::vec u_now;
  //arma::vec u_tt;
  //arma::vec temp;
  double* u_now;
  double* u_tt;
  double* temp;
  double* pOriginal;
  arma::mat A;

  char filename[160];

private:
  void setIC();
  void setA();
  void calcWave();
public:
  Wave(double a, double b, int h, double t0, double tend, double dt, double c);
  ~Wave();
};

}

#endif
