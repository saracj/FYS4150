#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#include <armadillo>
#include <fstream>
#include <sstream>
#include <string>
#include "celestialbodies.h"

class solarsystem{

private:
    double dt, length, m, M, G, v_kin, v_ang;
    vec fg, R, potential, kinetic, potential_energy, kinetic_energy, angular_momentum;
    mat F_g, F, ang_mom, vel_E, vel_ang1;
    mat accel, all_pos, all_vel, all_positions, all_velocities;
    mat ak1, vk1, ak2, vk2, ak3, vk3, ak4, vk4;

    mat RK4_pos, RK4_vel, RK4_next_pos, RK4_next_vel;

    mat verlet_next_pos, verlet_next_vel, verlet_pos, verlet_vel, verlet_next, previous_pos;

    vec i_vel, i_pos;

    vec potential_E(), kinetic_E(), ang_momentum();

    string filename;
    string filename2;
    std::ofstream outFile;
    std::ofstream outFile_E;

public:
    solarsystem(double time_step, string method_dt_endTime);
    ~solarsystem() {this->outFile.close(); this->outFile_E.close();}// this->outFile_vel.close();

    vector<celestialbodies*> objects;

    mat getForces();
    mat acceleration();
    void verlet(int i);
    void RK4();

    void AddObject(celestialbodies *);
    void setAllPositions(mat), setAllVelocities(mat);
    int getNumberOfObj();
    mat getAllPos(), getAllVel();

    void dumpToFile();
};

#endif // SOLARSYSTEM_H
