#include "solarsystem.h"
#include "celestialbodies.h"
#include <cmath>
#include <armadillo>

using namespace arma;
using namespace std;

solarsystem::solarsystem(double m_dt){
    this->dt = m_dt;
}

void solarsystem::AddObject(celestialbodies newobject){
    objects.push_back(newobject);
}

// Gravitational force working on one object by the other objects
vec solarsystem::getForces(celestialbodies object){
    vec F_g = zeros<vec>(2);
    for(this->i=0; this->i < getNumberOfObj(); this->i++){
        if(object.getID() == objects[i].getID()){ continue; }

        this->R = object.getDist(objects[i]);
        this->m = object.getM();
        this->M = objects[i].getM();
        this->G = 4*M_PI*M_PI; // Gravitational constant [Au^3 / yr^2 M_sun]
        this->fg = G*M*m*R/pow(norm(R), 3);
        F_g += fg;
    }
    //cout << "Force on " << object.getID() << ": "<< endl << F_g << endl;
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
void solarsystem::RK4(){
    k1 = zeros<vec>(2); k2 = zeros<vec>(2); k3 = zeros<vec>(2); k4 = zeros<vec>(2);
    K1 = zeros<vec>(2); K2 = zeros<vec>(2); K3 = zeros<vec>(2); K4 = zeros<vec>(2);
    // Loops over all the objects in the system.
    for(this->i=0; this->i < getNumberOfObj(); this->i++){
        if(objects[i].getID() == "Sun"){ continue; } // Keep sun stationary

        // Runge-Kutta, fourth order:
        RK4_vel = objects[i].getVel();
        RK4_pos = objects[i].getPos();
        //cout << RK4_vel << endl;

        k1 = acceleration(objects[i]);
        K1 = objects[i].getVel();
        cout << K1 << endl;
        objects[i].setPos(RK4_pos + 0.5*dt*K1);
        //cout << "Acceleration of object " << objects[i].getID() << ": "<< endl << k1 << endl;
        //cout << "Distance: " << endl << this->R  << endl;


        k2 = acceleration(objects[i]);
        K2 = K1 + 0.5*dt*k1;
        objects[i].setPos(RK4_pos + 0.5*dt*K2);

        k3 = acceleration(objects[i]);
        K3 = K1 + 0.5*dt*k2;
        objects[i].setPos(RK4_pos + 0.5*dt*K3);

        k4 = acceleration(objects[i]);
        K4 = K1 + 0.5*dt*k3;

        /*
        cout << "Acceleration to velocity:" << endl;
        cout << "k1 = " << endl << k1 << endl;
        cout << "k2 = " << endl << k2 << endl;
        cout << "k3 = " << endl << k3 << endl;
        cout << "k4 = " << endl << k4 << endl;
        cout << "Velocity to position:" << endl;
        cout << "K1 = " << endl << k1 << endl;
        cout << "K2 = " << endl << k2 << endl;
        cout << "K3 = " << endl << k3 << endl;
        cout << "K4 = " << endl << K4 << endl;
        */

        RK4_next_vel = RK4_vel + (dt/6.)*(k1 + 2*k2 + 2*k3 + k4);
        RK4_next_pos = RK4_pos + (dt/6.)*(K1 + 2*K2 + 2*K3 + K4);
        //cout << "Change in position: " << endl << (dt/6.)*(K1 + 2*K2 + 2*K3 + K4) << endl;

        objects[i].setVel(RK4_next_vel);
        objects[i].setPos(RK4_next_pos);
    }
}

int solarsystem::getNumberOfObj(){ return objects.size(); }


