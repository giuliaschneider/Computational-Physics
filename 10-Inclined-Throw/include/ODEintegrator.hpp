
#ifndef RK
#define RK

#include <armadillo>

namespace comphys{

class ODEintegrator{
protected:
  int d;
  int n_steps;
  double dt;
  arma::vec y0;
  arma::vec y;
  arma::mat output;
  double t;
  double t0;
  double tend;
  std::function<arma::vec(arma::vec,double)> pF;
  const char* vfilename;

public:
  ODEintegrator(arma::vec y0, double t0, double tend, int n_steps,std::function<arma::vec(arma::vec,double)> pF,const char* vfilename);

  void integrate();
  virtual void step();
};

class rk4: public ODEintegrator{
private:
    void step();
public:
  rk4(arma::vec y0, double t0, double tend, int n_steps,std::function<arma::vec(arma::vec,double)> pF,const char* vfilename);
};

}


#endif
