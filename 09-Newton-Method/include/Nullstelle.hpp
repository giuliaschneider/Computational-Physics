
#ifndef NULLSTELLE
#define NULLSTELLE

#include <armadillo>

namespace comphys{

arma::vec Newton(int d, arma::vec x0, arma::vec (*F)(arma::vec), arma::mat (*DF)(arma::vec), double rtol= 0.0000000001, int maxiter=200);
void printErrorNewton(arma::vec xstar, int d, arma::vec x0, arma::vec (*F)(arma::vec), arma::mat (*DF)(arma::vec), const char* vfilename="output.txt", double rtol= 0.0000000001, int maxiter=200);


arma::mat numericalGrad(int d,  arma::vec x0, arma::vec (*F)(arma::vec), double eps=0.0000000000000001);

arma::vec Secant(int d, arma::vec x0, arma::vec (*F)(arma::vec), double eps=0.0000000000000001, double rtol= 0.00001, int maxiter=100);
void printErrorSecant(arma::vec xstar, int d, arma::vec x0, arma::vec (*F)(arma::vec), const char* vfilename="output.txt", double rtol= 0.0000000001, int maxiter=200);

}

#endif
