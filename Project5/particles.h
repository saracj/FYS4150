#ifndef PARTICLES_H
#define PARTICLES_H
#include <armadillo>
#include <vector>

class particles{

private:
    // 2D case:
    // arma::vec position, newPosition;

    // 1D case:
    double position, newPosition;


public:
    // 2D case:
    // particles(arma::vec position, int number_of_dimensions);
    // arma::vec getPos();
    // void setPos(arma::vec newPosition);


    // 1D case:
    particles(double position);
    double getPos();
    void setPos(double newPosition);
};

#endif // PARTICLES_H
