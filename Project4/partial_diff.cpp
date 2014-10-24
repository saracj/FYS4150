#include "partial_diff.h"
#include <armadillo>

using namespace arma;
using namespace std;

partial_diff::partial_diff(double position_step, double end_time, double end_position, double D){
    this->dx = position_step; // Position step length
    this->dt = 1/(2*dx^2); // Demanded by stability: dt/dx^2 <= 1/2
    this->T = end_time;
    this->d = end_position;
    this->nt = T/dt; // Number of time steps
    this->nx = d/dx; // Number of position steps
    this->D = D; // Diffusion coeffictient
}


// Solves time evolution of the diffusion equation
// using the Explicit scheme
void partial_diff::EXPLICIT(mat u){
    C = D*dt/dx^2;

    for(int i=1; i<nx; i++){
        for(int j=1; j<nt; j++)

            u(i,j+1) = C*( u(i+1,j) - u(i,j) + u(i-1, j));
    }

    setU(u);
}


// Solves time evolution using the Implicit scheme
void partial_diff::IMPLICIT(){

}


// Solves time evolution using the Crank-Nicolson scheme
void partial_diff::CRANK_NICOLSON(){

}

// Solves the position for a tridagonal matrix
void partial_diff::TRIDIAG(mat B){

}

void partial_diff::setU(mat new_u){ this->u = new_u; }
void partial_diff::getU(){ return this->u; }
