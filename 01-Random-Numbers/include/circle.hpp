/**
    @brief: prints random points homogeneously distributed within a circle
    @param numberRNG:   number of random points
    @return void
*/
void uniform_circle(int numberRNG){
  int R = 1;
  double phi = 0.0;
  double r = 0.0;
  for(int i=0;i<numberRNG;i++){
    phi = (2*M_PI*rand())/RAND_MAX;
    r = R*sqrt((1.0*rand())/RAND_MAX);
    cout << r*cos(phi) << '\t' << r*sin(phi) << endl;
  }
}
