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
    double D  = 1., dt = 1e-3, l0 = sqrt(2.*D*dt), t_end = 1., d = 1.;
    int N  = 1e4, dimensions = 1, nt = t_end/dt;

    // Construct system of particles
    jump system(dimensions, nt, l0, d, N);

    system.particle_loop();

    system.histogram();


    return 0;
}
