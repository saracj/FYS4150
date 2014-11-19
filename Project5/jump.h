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
    double eps, xnew, xold, l0, d, pos;
    int dim, nu, nt, k_end;
    int counter1, counter2, counter3, counter4; // If-test counters
    arma::mat all_pos;
    //arma::vec pos;
    std::vector<particles*> u;
    std::vector<int> erase_indices;

    void left_right(double random_number, int position_step_i);

public:
    jump(int dimensions, int number_of_timesteps, double position_step_length, double interval_length); // Constructor

    void AddParticle(particles*);
    void particle_loop();
    int getNumberOfParticles();
    arma::mat getAllPositions();

};

#endif // JUMP_H
