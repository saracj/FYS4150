#include "solarsystem.h"
#include <armadillo>

solarsystem::solarsystem()
{
}

vec solarsystem::getForces(celestialbodies object){
    vec F_g(2);
    r = object.diastance(objects[i]);
    m = object.getM();
    M = objects[i].getM();
    F_g = G*M*m*(object.getPos())*r/pow(norm(r, 2), 3);
    return F_g;
}

void solarsystem::acceleration(celestialbodies object){
    acceleration = getForce(object)/object.getM();
    return acceleration;
}

// Advances one object one time step ahead
void solarsystem::advance(object){
    a1 = acceleration(object.getPos(object));
    a2 = acceleration(object.getPos(object) + 0.5*k1);
    a3 = acceleration(object.getPos(object) + 0.5*k2);
    a4 = acceleration(object.getPos(object) + k3);

    // Runge-Kutta, fourth order:
    k1 = dt*a1;
    k2 = dt*a2;
    k3 = dt*a3;
    k4 = dt*a4;
    vel = vel + (1/6.)*(k1 + 2*k2 + 2*k3 + k4);

    // Position:
    pos(i+1, i+1) = pos(i,i) + dt*v(i,i);
}

int solarsystem::getNumberOfObj(){
}


