#include <iostream>
#include <armadillo>
#include "solarsystem.h"
#include "celestialbodies.h"

using namespace std;
using namespace arma;

int main(){
    double dt = 1e-3; // time step, [years]
    double r = 1.; // Distance from earth to sun [AU]
    double G = 1.2e-21; // Gravitational constant [Au^3 / yr^2 M_sun]
    double T = 2.;
    double n = T/dt;
    double vx = G*1./1.; // vr^2 = G*M_sun
    double vy = 0;
    int i;
    vec pos_earth(2), vel_earth(2), pos_sun(2), vel_sun(2), time(n);
    vec NEXT_earth(4);
    mat earth_pos = zeros<mat>(n, 2);
    mat earth_vel = zeros<mat>(n, 2);

    // Initial conditions, earth:
    vel_earth(0) = vx; vel_earth(1) = vy; pos_earth(0) = 0; pos_earth(1) = r;
    // Initial conditions, Sun:
    vel_sun(0) = 0; vel_sun(1) = 0; pos_sun(0) = 0; pos_sun(1) = 0;

    solarsystem MySolarsystem;
    // object(string name, mass, position, velocity)
    celestialbodies sun("Sun", 1., pos_sun, vel_sun);
    celestialbodies earth("Earth", 1e-6, pos_earth, vel_earth);

    MySolarsystem.AddObject(sun);
    MySolarsystem.AddObject(earth);

    for(i=0; i<n-1; i++){
        NEXT_earth = MySolarsystem.advance(earth); // (x, y, vx, vy)
        earth_pos(i, 0) = NEXT_earth(0);
        earth_pos(i, 1) = NEXT_earth(1);
        earth_vel(i, 0) = NEXT_earth(2);
        earth_vel(i, 1) = NEXT_earth(3);
        time[i+1] = time[i] + dt;
    }
    return 1;
}
