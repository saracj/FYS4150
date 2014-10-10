#include <iostream>
#include <armadillo>

using namespace std;

int main()
{

}

void RK4(vec *u, vec t, double f, int i){ //Constructor
    // Calculates the u[i+1] value using the
    // Runge-Kutta, fourth order.
    // OUTPUT: unew = u[i+1]
    vec U = *u;
    dt = t[i+1] - t[i]; // time step
    k1 = dt*f(U(i), t(i));
    k2 = dt*f(U(i) + 0.5*k1, t(i) + 0.5*dt);
    k3 = dt*f(U(i) + 0.5*k2, t(i) + 0.5*dt);
    k4 = dt*f(U(i) + k3, t(i) + dt);
    U(i+1) = U(i) + (1/6.)*(k1 + 2*k2 + 2*k3 + k4);
}
