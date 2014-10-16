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
    for(this->i=0; this->i < getNumberOfObj(); this->i++){
        if(object.getID() == objects[i].getID()){
            continue; }
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
    accel = getForces(object)/object.getM();
    return accel;
}

vec solarsystem::verlet(celestialbodies object){
    verlet_pos = object.getPos();
    verlet_next_pos = 2*verlet_pos + dt*dt*acceleration(object) - previous_pos;
    previous_pos = verlet_pos;
    object.setF(zeros<vec>(2));
    return verlet_next_pos;
}

// Advances one object one time step ahead
vec solarsystem::RK4(celestialbodies object){

    // Runge-Kutta, fourth order:
    RK4_vel = object.getVel();
    RK4_pos = object.getPos();
    cout << "initiation of RK complete"<< endl;

    k1 = acceleration(object);
    K1 = object.getVel();
    // This needs to be done between each k because
    // the force depends on position, meaning
    // that we need to update the position
    object.setPos(RK4_pos + 0.5*dt*K1);
    k2 = acceleration(object);
    K2 = object.getVel();

    object.setPos(RK4_pos + 0.5*dt*K2);
    k3 = acceleration(object);
    K3 = object.getVel();

    object.setPos(RK4_pos + 0.5*dt*K3);
    k4 = acceleration(object);
    K4 = object.getVel();

    RK4_next_vel = RK4_vel + (dt/6.)*(k1 + 2*k2 + 2*k3 + k4);
    RK4_next_pos = RK4_pos + (dt/6.)*(K1 + 2*K2 + 2*K3 + K4);

    object.setVel(RK4_next_vel);
    object.setPos(RK4_next_pos);

    RK4_next = zeros<vec>(4);
    RK4_next(0) = RK4_next_pos(0);
    RK4_next(1) = RK4_next_pos(1);
    RK4_next(2) = RK4_next_vel(0);
    RK4_next(3) = RK4_next_vel(1);

    object.setF(zeros<vec>(2));
    return RK4_next;
    // Saving position and time to arrays
    // *pos_mat[i+1, i+1] = next_pos;
    // *vel_mat[i+1, i+1] = next_vel;
}

int solarsystem::getNumberOfObj(){ return objects.size(); }


