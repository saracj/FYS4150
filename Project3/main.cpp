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
    vec pos_earth(2), vel_earth(2), pos_sun(2), vel_sun(2), time(n);

    // Initial conditions, earth:
    vel_earth(0) = vx; vel_earth(1) = vy; pos_earth(0) = 0; pos_earth(1) = r;
    // Initial conditions, Sun:
    vel_sun(0) = 0; vel_sun(0) = 0; pos_sun(0) = 0; pos_sun(1) = 0;

    solarsystem MySolarsystem;
    // object(string name, mass, position, velocity)
    celestialbodies sun("Sun", 1., pos_sun, vel_sun);
    celestialbodies earth("Earth", 1e-6, pos_earth, vel_earth);

    MySolarsystem.AddObject(sun);
    MySolarsystem.AddObject(earth);

    int i = 0;
    mat earth_pos = zeros<mat>(n, 2);
    mat earth_vel = zeros<mat>(n, 2);
    int t = 0;
    while(t < T){
        MySolarsystem.advance(earth, &earth_pos, &earth_vel, i);
        time[i+1] = time[i] + dt;
        t += dt;
        i += 1;
    }
}
