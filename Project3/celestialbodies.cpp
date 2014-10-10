#include "celestialbodies.h"
#include <armadillo>

celestialbodies::celestialbodies(double m, double M, double r, vec init_pos, vec init_vel, double dt){
    // The variables and parameters to be used in the class celestialbodies
    // need to be specified by this->paramater. We give the value of these
    // parameters in the main-file or in the solarsystem.cpp. This constructor
    // call decides which two bodies are being calculated
    this->m = m;
    this->M = M;
    this->r = r;
    pos(0,0) = init_pos(0);
    pos(0,1) = init_pos(1);
    vel(0,0) = init_vel(0);
    vel(0,1) = init_vel(1);
    F_g  = (0,0);

    for(i=0;i<n;i++){
        RK4_vel();
        position();
    }
}

vec celestialbodies::f(vec position, double t){
    F_g(0) = G*M*m*position(i,0)/(r*r);
    F_g(1) = G*M*m*position(i,1)/(r*r);
    acceleration = F_g/m;
    return acceleration;
}

void celestialbodies::RK4_vel(){
    // Calculates the vel[i+1] value using the
    // Runge-Kutta, fourth order.

    // Velocity
    k1 = dt*f(pos(i, i), t(i));
    k2 = dt*f(pos(i, i) + 0.5*k1, t(i) + 0.5*dt);
    k3 = dt*f(pos(i, i) + 0.5*k2, t(i) + 0.5*dt);
    k4 = dt*f(pos(i, i) + k3, t(i) + dt);
    vel(i+1, i+1) = vel(i, i) + (1/6.)*(k1 + 2*k2 + 2*k3 + k4);
}

void celestialbodies::position(){
    pos(i+1, i+1) = pos(i,i) + dt*v(i,i);
}
