
#ifndef PDEINTEGRATOR
#define PDEINTEGRATOR

#include <armadillo>


class PDEintegrator{
protected:
  int N;
  int n_innergrid;
  double atol;
  double dx;
  arma::vec psi;
  arma::vec b;
  std::string vfilename;
  double delta;
public:
  PDEintegrator(int N, arma::vec b, double atol, std::string vfilename);
  void integrate();
  virtual void step();
};

class RelaxationMethods: public PDEintegrator{
public:
  RelaxationMethods(int N, arma::vec b, double atol, std::string vfilename);
  void step();
  double update_psi(int position);
};

class Jacobi: public RelaxationMethods{
public:
  Jacobi(int N, arma::vec b, double atol, std::string vfilename);
  void step();
private:
  arma::vec psi_new;
};

class GaussSeidel: public RelaxationMethods{
public:
  GaussSeidel(int N, arma::vec b, double atol, std::string vfilename);
  void step();
};


#endif
