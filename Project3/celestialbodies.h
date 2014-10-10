#ifndef CELESTIALBODIES_H
#define CELESTIALBODIES_H
#include <armadillo>

using namespace arma;

class celestialbodies{
private:
    vec k1, k2, k3, k4, init_pos, init_vel, acceleration;
    double dt, M, m, r;
    vec F_g = zeros<vec>(2);
    int i;
public:
    mat pos = zeros<mat>(n, 2);
    mat vel = zeros<mat>(n, 2);
    vec t;

    celestialbodies(double m, double M, vec init_pos, vec init_vel, double dt);
};

#endif // CELESTIALBODIES_H
