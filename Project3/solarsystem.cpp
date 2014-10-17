#include "solarsystem.h"
#include "celestialbodies.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <armadillo>

using namespace arma;
using namespace std;

solarsystem::solarsystem(double dt){
    this->outFile.open("/scratch/saracj/Data_RK4.dat", ios::out); //("../Project3/Data_RK4.dat", ios::out);
    this->dt = dt;
}

void solarsystem::AddObject(celestialbodies *newobject){
    objects.push_back(newobject);
}

// Gravitational force working on one object by the other objects
mat solarsystem::getForces(){
    G = 4*M_PI*M_PI; // Gravitational constant [Au^3 / yr^2 M_sun]
    F_g = zeros<mat>(getNumberOfObj(), 2);

    for(int i=0; i < getNumberOfObj(); i++){  // i=0, k=1
        for(int k=i+1; k < getNumberOfObj(); k++) { // i=1, k=0

            if(objects[k]->getID() == objects[i]->getID()){ continue; }

            R = objects[i]->getDist(*objects[k]); // cout << R << endl;
            m = objects[i]->getM(); // cout << m << endl;
            M = objects[k]->getM(); // cout << M << endl;

            fg =  G*M*m*R/ pow(norm(R), 3);
            F_g.row(i) += fg.t();
            F_g.row(k) -= fg.t(); // Newtons third law
        }
    }
    return F_g;
}

// Acceleration of system, calls getForces().
mat solarsystem::acceleration(){
    F = getForces();
    // cout << F << endl;
    accel = zeros<mat>(getNumberOfObj(), 2);
    for(int i=0; i < getNumberOfObj(); i++){
        accel.row(i) = F.row(i)/objects[i]->getM();
    }
    return accel;
}

// Verlet method
void solarsystem::verlet(int i){
    all_vel = zeros<mat>(getNumberOfObj(), 2);
    all_pos = zeros<mat>(getNumberOfObj(), 2);

    for(int j=0; j < getNumberOfObj(); j++){
        // Saves the positions of all the objects in the
        // system in a nx2 matrix, where n is the number of
        // objects
        all_vel.row(j) = objects[j]->getVel().t();
        all_pos.row(j) = objects[j]->getPos().t();

    }

    setAllVelocities(all_vel);
    setAllPositions(all_pos);

    verlet_pos = getAllPos();
    if(i == 0){// Euler
        verlet_next_pos = verlet_pos + getAllVel()*dt + (1./2)*acceleration()*dt*dt;
        previous_pos = verlet_pos;
        setAllPositions(verlet_next_pos);
    }
    else{
        verlet_next_pos = 2*verlet_pos + dt*dt*acceleration() - previous_pos;
        previous_pos = verlet_pos;
        setAllPositions(verlet_next_pos);
    }


    this->dumpToFile();
}

// Fourth order Runge-Kutta
void solarsystem::RK4(){

    all_vel = zeros<mat>(getNumberOfObj(), 2);
    all_pos = zeros<mat>(getNumberOfObj(), 2);

    for(int i=0; i < getNumberOfObj(); i++){
        // Saves the positions of all the objects in the
        // system in a nx2 matrix, where n is the number of
        // objects
        all_vel.row(i) = objects[i]->getVel().t();
        all_pos.row(i) = objects[i]->getPos().t();
    }

    setAllVelocities(all_vel);
    setAllPositions(all_pos);

    RK4_vel = getAllVel();
    RK4_pos = getAllPos();

    ak1 = acceleration();
    vk1 = getAllVel();

    setAllVelocities(RK4_vel + 0.5*dt*ak1);
    setAllPositions(RK4_pos + 0.5*dt*vk1);

    //cout << RK4_vel << endl;
    //cout << RK4_pos << endl;

    ak2 = acceleration();
    vk2 = vk1 + 0.5*dt*ak1;

    setAllVelocities(RK4_vel + 0.5*dt*ak2);
    setAllPositions(RK4_pos + 0.5*dt*vk2);

    ak3 = acceleration();
    vk3 = vk2 + 0.5*dt*ak2;

    setAllVelocities(RK4_vel + dt*ak3);
    setAllPositions(RK4_pos + dt*vk3);

    ak4 = acceleration();
    vk4 = vk3 + dt*ak3;

    RK4_next_vel = RK4_vel + (dt/6.)*(ak1 + 2*ak2 + 2*ak3 + ak4);
    RK4_next_pos = RK4_pos + (dt/6.)*(vk1 + 2*vk2 + 2*vk3 + vk4);
    // cout << "Change in position: " << endl <<(dt/6.)*(vk1 + 2*vk2 + 2*vk3 + vk4) << endl;

    setAllVelocities(RK4_next_vel);
    setAllPositions(RK4_next_pos);

    this->dumpToFile();
}

int solarsystem::getNumberOfObj(){ return objects.size(); }

// Set the positions of all objects in system
void solarsystem::setAllPositions(mat newPositions){
    all_positions = newPositions;

    for(int i=0; i < getNumberOfObj(); i++){
        // Sets position of individual objects

        i_pos = newPositions.row(i).t();
        objects[i]->setPos(i_pos);
    }
}

// Set the velocities of all objects in system
void solarsystem::setAllVelocities(mat newVelocities){
    all_velocities = newVelocities;

    for(int i=0; i < getNumberOfObj(); i++){
        // Sets velocity of individual objects

        i_vel = newVelocities.row(i).t();
        objects[i]->setVel(i_vel);
    }
}

mat solarsystem::getAllPos(){ return all_positions; }
mat solarsystem::getAllVel(){ return all_velocities; }


void solarsystem::dumpToFile() {

    for (int i = 0; i < getNumberOfObj(); i++) {
        for (int j = 0; j < 2; j++) {
            this->outFile << objects[i]->getPos()[j] << " ";
        }
    }
    this->outFile << endl;
}

