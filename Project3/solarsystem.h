#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#include <armadillo>
#include <fstream>
#include <sstream>
#include <string>
#include "celestialbodies.h"

class solarsystem{

private:
    double dt, length, m, M, G;
    vec fg, R;
    mat F_g, F;
    mat accel, all_pos, all_vel;
    mat ak1, vk1, ak2, vk2, ak3, vk3, ak4, vk4;

    mat all_accel, all_positions, all_velocities;
    mat RK4_pos, RK4_vel, RK4_next_pos, RK4_next_vel;

    mat verlet_next_pos, verlet_pos, verlet_vel, verlet_next, previous_pos;

    vec i_vel, i_pos;

    string filename;
    std::ofstream outFile;

public:
    solarsystem(double time_step, string method_dt_endTime);
    ~solarsystem() {this->outFile.close();}

    vec position;
    vec velocity;
    vector<celestialbodies*> objects;

    int getNumberOfObj();
    mat getForces();
    mat acceleration();
    void AddObject(celestialbodies *);
    void RK4();
    void verlet(int i);
    void setAllPositions(mat), setAllVelocities(mat);
    mat getAllPos(), getAllVel();
    void dumpToFile();

};

#endif // SOLARSYSTEM_H
