#include "solarsystem.h"
#include "celestialbodies.h"
#include <cmath>
#include <armadillo>

using namespace arma;
using namespace std;

solarsystem::solarsystem(){
}

void solarsystem::AddObject(celestialbodies newobject){
    objects.push_back(newobject);
}

// Gravitational force working on one object by the other objects
vec solarsystem::getForces(celestialbodies object){
    vec F_g = zeros<vec>(2);
    cout << getNumberOfObj() << endl;
    for(i=0; i < getNumberOfObj(); i++){
        if(object.getID() == objects[i].getID()){ continue; }
        R = object.getDist(objects[i]);
        m = object.getM();
        M = objects[i].getM();
        G = 1.2e-21; // Gravitational constant [Au^3 / yr^2 M_sun]
        F_g += G*M*m*R/pow(norm(R), 3);
    }
    return F_g;
}

// Acceleration of one object
vec solarsystem::acceleration(celestialbodies object){
    cout << getForces(object) << endl;
    accel = getForces(object)/object.getM();
    return accel;
}

// Advances one object one time step ahead
vec solarsystem::advance(celestialbodies object){

    // Runge-Kutta, fourth order:
    vel = object.getVel();
    pos = object.getPos();

    k1 = acceleration(object);
    K1 = object.getVel();

    // This needs to be done between each k because
    // the force depends on position, meaning
    // that we need to update the position
    object.setPos(pos + 0.5*dt*K1);
    k2 = acceleration(object);
    K2 = object.getVel();

    object.setPos(pos + 0.5*dt*K2);
    k3 = acceleration(object);
    K3 = object.getVel();

    object.setPos(pos + 0.5*dt*K3);
    k4 = acceleration(object);
    K4 = object.getVel();

    next_vel = vel + (1/6.)*(k1 + 2*k2 + 2*k3 + k4);
    next_pos = pos + (1/6.)*(K1 + 2*K2 + 2*K3 + K4);
    object.setVel(next_vel);
    object.setPos(next_pos);

    vec next;
    next(0) = next_pos(0);
    next(1) = next_pos(1);
    next(2) = next_vel(0);
    next(3) = next_vel(1);
    return next;
    // Saving position and time to arrays
    // *pos_mat[i+1, i+1] = next_pos;
    // *vel_mat[i+1, i+1] = next_vel;
}

int solarsystem::getNumberOfObj(){ return objects.size(); }


