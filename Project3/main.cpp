#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(){
    double  dt = ; // time step
    M_sun = 1.; // solar mass
    M_earth = 1e-6; // earth mass
    // Initial velocity (y-direction)
    v = sqrt(G*M_sun/r);
    celestialbodies earth(M, (1,0), (0,0), dt); //position and velocity of earth
}
