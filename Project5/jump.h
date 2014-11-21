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
    double l0, d;
    int dim, nu, nt;
    int counter1, counter2, counter3, counter4; // If-test counters
    arma::mat all_pos;
    //arma::vec pos;
    std::vector<int> erase_indices;

    void left_right(double random_number, int position_step_i);

public:
    jump(int dimensions, int number_of_timesteps, double position_step_length, double interval_length); // Constructor

    std::vector<particles*> u;
    void AddParticle(particles*);
    void particle_loop();
    void histogram();
    int getNumberOfParticles();

};

#endif // JUMP_H
