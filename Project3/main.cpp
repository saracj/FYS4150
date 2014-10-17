#include <iostream>
#include <armadillo>
#include <cmath>
#include "solarsystem.h"
#include "celestialbodies.h"

using namespace std;
using namespace arma;

int main(){
    double r = 1.; // Distance from earth to sun [AU]
    double G = 4*M_PI*M_PI; // Gravitational constant [Au^3 yr^-2 M_sun^-1]
    int n = 5000000.; // number of steps
    double T = 500.; // end time of simulation [years]
    double dt = T/n; // time step, [years]
    double vx = 2*M_PI; // v^2 * r = G*M_sun -- v = sqrt(G*M_sun/r)
    double vy = 0;
    int j;

    vec pos_earth(2), vel_earth(2), pos_sun(2), vel_sun(2);
    //vec time = zeros<vec>(n);
    //mat earth_pos = zeros<mat>(n, 2);

    // Initial conditions
    vel_earth(0) = vx; vel_earth(1) = vy; pos_earth(0) = 0; pos_earth(1) = r;
    vel_sun(0) = 0; vel_sun(1) = 0; pos_sun(0) = 0; pos_sun(1) = 0;

    solarsystem MySolarsystem(dt);
    celestialbodies sun("Sun", 1., pos_sun, vel_sun);
    celestialbodies earth("Earth", 3e-6, pos_earth, vel_earth);

    MySolarsystem.AddObject(&sun);
    MySolarsystem.AddObject(&earth);

    //earth_pos.row(0) = pos_earth.t();
    for(j=0; j<n-1; j++){

        // Print progress.
        if (j % (n/1000) == 0) {
            printf("Progress: %5.1f %% \r", 100*j/ ((double) n));
            fflush(stdout);
        }

        //MySolarsystem.RK4();
        MySolarsystem.verlet(j);
        //earth_pos.row(j+1) = earth.getPos().t();// RK4 is calculated as a column vector
        //time(j+1) = time(j) + dt;
    }
    //cout << "Position vector of earth" << endl << earth_pos << endl;
    return 0;
}



/*
 * #include <iostream>
 * #include <ofstream>
 *
 * ofstream outFile;
 * outFile.open("filename.txt", ios::out);
 *
 * for (int i = 0; i < n; i ++) {
 *      outFile << data...
 * }
 *
 * outFile.close();
 */
