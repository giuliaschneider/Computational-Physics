Many ordinary differential equations, as for example the trajectory of a ball in the presence of air resistance, can't be solved analytically, but a solution has to be found numerically. In this exercise, the just mentioned trajectory was to be calculated numerically and the angle at which the ball has the maximum range was to be determined. For this purpose, the Runge-Kutta of 4th stage was implemented in C++.

The class <em>Throw</em> wraps up the parameters and right hand side function of the inclined throw problem

The class <em> ODEintegrator</em> is a general class for the integration of autonom first order ODE with n<sub>steps</sub>.

# Required Libraries:

**ARMADILLO** - C++ linear algebra library

