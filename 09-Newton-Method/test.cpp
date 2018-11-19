arma::vec F1(arma::vec x){
    arma::vec Fx(2);
    Fx(0) = exp(x(0)*x(1)) + pow(x(0),2) + x(1) - 1.2;
    Fx(1) = pow(x(0),2)  + pow(x(1),2)  + x(0) - 0.55;
    return Fx;
  }


arma::mat DF1(arma::vec x){
    arma::mat DFx(2,2);
    DFx(0,0) = x(1)*exp(x(0)*x(1)) + 2.0*x(0);
    DFx(0,1) = x(0)*exp(x(0)*x(1)) + 1.0;
    DFx(1,0) = 2.0*x(0) + 1.0;
    DFx(1,1) =  2.0*x(1);
    return DFx;
  }
