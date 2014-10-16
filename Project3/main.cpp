#include <iostream>
#include <armadillo>
#include <cmath>
#include "solarsystem.h"
#include "celestialbodies.h"

using namespace std;
using namespace arma;

int main(){
    double r = 1.; // Distance from earth to sun [AU]
    double G = 4*M_PI*M_PI; // Gravitational constant [Au^3 yr^-2 M_sun^-1]
    double n = 50.; // number of steps
    double T = 2.; // end time of simulation [years]
    double dt = T/n; // time step, [years]
    double vx = sqrt(G); // v^2 * r = G*M_sun -- v = sqrt(G*M_sun/r)
    double vy = 0;
    int i;
    vec pos_earth(2), vel_earth(2), pos_sun(2), vel_sun(2), RK4_earth(2);
    vec time = zeros<vec>(n);
    mat earth_pos = zeros<mat>(n, 2);
    // mat earth_vel = zeros<mat>(n, 2);

    // Initial conditions, earth:
    vel_earth(0) = vx; vel_earth(1) = vy; pos_earth(0) = 0; pos_earth(1) = r;
    // Initial conditions, Sun:
    vel_sun(0) = 0; vel_sun(1) = 0; pos_sun(0) = 0; pos_sun(1) = 0;

    solarsystem MySolarsystem(dt);
    // object(string name, mass, position, velocity)
    celestialbodies sun("Sun", 1., pos_sun, vel_sun);
    celestialbodies earth("Earth", 1e-6, pos_earth, vel_earth);

    MySolarsystem.AddObject(sun);
    MySolarsystem.AddObject(earth);
    earth_pos.row(0) = pos_earth.t();
    for(i=0; i<n-1; i++){
        MySolarsystem.RK4(); // (x, y), RK4_earth = earth.getPos()
        cout << earth.getPos() << endl;
        earth_pos.row(i+1) = earth.getPos().t();// RK4_earth is calculated as a column vector
        time(i+1) = time(i) + dt;
    }
    cout << "Position vector of earth" << endl << earth_pos << endl;
    return 0;
}
