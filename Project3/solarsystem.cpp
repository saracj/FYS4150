#include "solarsystem.h"
#include "celestialbodies.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <armadillo>
using namespace arma;
using namespace std;

solarsystem::solarsystem(double dt, string method_dt_T, string method){
    filename = "../Project3/Data/Data_" + method_dt_T + ".dat";
    filename2 = "../Project3/Data/Energy_" + method_dt_T + ".dat";
    filename_sun = "../Project3/Data/sun_"+method+".dat";
    filename_merc = "../Project3/Data/merc_"+method+".dat";
    filename_ven = "../Project3/Data/ven_"+method+".dat";
    filename_earth = "../Project3/Data/earth_"+method+".dat";
    filename_mars = "../Project3/Data/mars_"+method+".dat";
    filename_jup = "../Project3/Data/jup_"+method+".dat";
    filename_sat = "../Project3/Data/sat_"+method+".dat";
    filename_ur = "../Project3/Data/ur_"+method+".dat";
    filename_nep = "../Project3/Data/nep_"+method+".dat";

    cout << filename << endl;
    cout << filename2 << endl;

    this->outFile.open(filename.c_str(), ios::out);
    this->outFile_0.open(filename_sun.c_str(), ios::out);
    this->outFile_1.open(filename_merc.c_str(), ios::out);
    this->outFile_2.open(filename_ven.c_str(), ios::out);
    this->outFile_3.open(filename_earth.c_str(), ios::out);
    this->outFile_4.open(filename_mars.c_str(), ios::out);
    this->outFile_5.open(filename_jup.c_str(), ios::out);
    this->outFile_6.open(filename_sat.c_str(), ios::out);
    this->outFile_7.open(filename_ur.c_str(), ios::out);
    this->outFile_8.open(filename_nep.c_str(), ios::out);

    this->dt = dt;
}

void solarsystem::AddObject(celestialbodies *newobject){
    objects.push_back(newobject);
}

// Gravitational force working on one object by the other objects
mat solarsystem::getForces(){
    G = 4*M_PI*M_PI; // Gravitational constant [Au^3 / yr^2 M_sun]
    F_g = zeros<mat>(getNumberOfObj(), 2);
    for(int i=0; i < getNumberOfObj(); i++){

        if(objects[i]->getID() == "Sun"){ continue;} // Keep Sun fixed
        for(int k=0; k < getNumberOfObj(); k++) {

            if(objects[k]->getID() == objects[i]->getID()){ continue; }

            R = objects[i]->getDist(*objects[k]); // cout << R << endl;
            m = objects[i]->getM(); // cout << m << endl;
            M = objects[k]->getM(); // cout << M << endl;

            fg = G*M*m*R/ pow(norm(R), 3);
            F_g.row(i) += fg.t();
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
    if(i == 0){

        verlet_next_pos = verlet_pos + getAllVel()*dt + (1./2)*acceleration()*dt*dt;
        previous_pos = verlet_pos;
        setAllPositions(verlet_next_pos);
    }
    else{

        verlet_next_pos = 2*verlet_pos + dt*dt*acceleration() - previous_pos;
        previous_pos = verlet_pos;
        setAllPositions(verlet_next_pos);
    }

    if(getNumberOfObj() < 3){ // Only interested in this for the two-body problem
        potential_energy = potential_E();
        kinetic_energy = kinetic_E();
        angular_momentum = ang_momentum();
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

    if(getNumberOfObj() < 3){ // Only interested in this for the two-body problem
        potential_energy = potential_E();
        kinetic_energy = kinetic_E();
        angular_momentum = ang_momentum();
    }

    this->dumpToFile();
}


vec solarsystem::potential_E(){
    potential = zeros<vec>(getNumberOfObj());

    G = 4*M_PI*M_PI; // Gravitational constant [Au^3 / yr^2 M_sun]
    for(int i = 0; i < getNumberOfObj(); i++){
        for(int k=0; k < getNumberOfObj(); k++){
            if(objects[k]->getID() == objects[i]->getID()){ continue; }

            potential(i) = -G * objects[i]->getM() * objects[k]->getM() / norm(objects[i]->getDist(*objects[k]));
        }
    }
    return potential;
}


vec solarsystem::kinetic_E(){
    kinetic = zeros<vec>(getNumberOfObj());
    vel_E = getAllVel();

    for(int i = 0; i < getNumberOfObj(); i++){
        v_kin  = norm(vel_E.row(i));

        kinetic(i) = (1./2)* objects[i]->getM() *v_kin*v_kin;
    }
    return kinetic;
}


vec solarsystem::ang_momentum(){
    ang_mom = zeros<vec>(getNumberOfObj());
    vel_ang1 = getAllVel();

    for(int i = 0; i < getNumberOfObj(); i++){
        v_ang = norm(vel_ang1.row(i));

        for(int k=0; k < getNumberOfObj(); k++){
            if(objects[k]->getID() == objects[i]->getID()){ continue; }

            if(getNumberOfObj() < 3){ // L = mv x r
                ang_mom(i) = norm(objects[i]->getDist(*objects[k])) * objects[i]->getM() * v_ang;}
        }
    }
    return ang_mom;
}

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
int solarsystem::getNumberOfObj(){ return objects.size(); }


// Writes to file
void solarsystem::dumpToFile() {

    for (int i = 0; i < getNumberOfObj(); i++) {
        for (int j = 0; j < 2; j++) {

            this->outFile << objects[i]->getPos()[j] << " ";
            if(objects[i]->getID() == "Sun"){ this->outFile_0 << objects[i]->getPos()[j] << " ";}
            if(objects[i]->getID() == "Mercury"){ this->outFile_1 << objects[i]->getPos()[j] << " ";}
            if(objects[i]->getID() == "Venus"){ this->outFile_2 << objects[i]->getPos()[j] << " ";}
            if(objects[i]->getID() == "Earth"){ this->outFile_3 << objects[i]->getPos()[j] << " ";}
            if(objects[i]->getID() == "Mars"){ this->outFile_4 << objects[i]->getPos()[j] << " ";}
            if(objects[i]->getID() == "Jupiter"){ this->outFile_5 << objects[i]->getPos()[j] << " ";}
            if(objects[i]->getID() == "Saturn"){ this->outFile_6 << objects[i]->getPos()[j] << " ";}
            if(objects[i]->getID() == "Uranus"){ this->outFile_7 << objects[i]->getPos()[j] << " ";}
            if(objects[i]->getID() == "Neptune"){ this->outFile_8 << objects[i]->getPos()[j] << " ";}
        }
        if(getNumberOfObj() < 3){ // Only interested in this for the two-body problem

            this->outFile_E << potential_energy(i) << " " << kinetic_energy(i) << " " << angular_momentum(i) << " ";
            }
    }
    this->outFile << endl;
    this->outFile_E << endl;
    this->outFile_0 << endl;
    this->outFile_1 << endl;
    this->outFile_2 << endl;
    this->outFile_3 << endl;
    this->outFile_4 << endl;
    this->outFile_5 << endl;
    this->outFile_6 << endl;
    this->outFile_7 << endl;
    this->outFile_8 << endl;
}
