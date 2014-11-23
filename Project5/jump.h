#ifndef JUMP_H
#define JUMP_H
#include <armadillo>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "particles.h"

class jump{
private:
    double D, d, l0, l, dt, tolerance;
    int dim, nu, nt, N;
    int counter1, counter2, counter3, counter4; // If-test counters
    arma::mat all_pos;
    //arma::vec pos;
    std::vector<int> erase_indices;

    void left_right(double random_number, int position_step_i, double step_length);

public:
    jump(int dimensions, int time_steps, double time_step_length, double position_step_length, double diffusion_coeff, double position_interval, int particles_at_x0); // Constructor

    std::vector<particles*> u;
    void AddParticle(particles*);
    void particle_loop();
    void histogram();
    void writeToFile(std::string filename, std::vector<particles*> data);
    int getNumberOfParticles();

};

#endif // JUMP_H
