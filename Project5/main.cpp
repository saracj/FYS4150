#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <armadillo>
#include <vector>
#include "jump.h"
#include "particles.h"

using namespace std;
using namespace arma;

int main(){
    int N  = 1e4;        // Number of particles at x0
    int dimensions = 1;

    double D  = 1.;            // Diffusion coefficient

    double dt = 1e-3;          // Time step
    double l0 = sqrt(2.*D*dt); // Step length
    double t_end = 3;          // Final simulation time
    double d = 1.;             // length of x-interval
    int    nt = t_end/dt;      // Number of time steps
    //int    nx = d/l0;          // Number of position steps/''boxes''


    // Construct system of particles
    jump system(dimensions, nt, l0, d);

    // Construct u-vector:
    for(int k=0; k<=N; k++){
        particles part(0.);
        system.AddParticle(&part);
    }

    system.particle_loop();

    mat system_positions = system.getAllPositions();

    mat sys = system_positions + 1;

    return 0;
}
