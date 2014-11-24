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
    double D  = 0.1, dt = 1e-3, t_end = 4., d = 1.;
    int N  = 1e3, dimensions = 1, nt = t_end/dt;

    cout << nt << endl;

    // Construct system of particles
    jump system(dimensions, nt, dt, D, d, N);

    system.particle_loop();
    system.histogram();


    return 0;
}
