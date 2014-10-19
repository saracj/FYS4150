#include <iostream>
#include <armadillo>
#include <cmath>
#include "solarsystem.h"
#include "celestialbodies.h"

using namespace std;
using namespace arma;

int main(){

    int j;
    int n = 1000000; // number of steps

    double r = 1.; // Distance from earth to sun [AU]
    double G = 4*M_PI*M_PI; // Gravitational constant [Au^3 yr^-2 M_sun^-1]
    double T = 50.; // end time of simulation [years]
    double dt = T/n; // time step, [years]
    double vx = 6.28616;// v^2 * r = G*M_sun -- v = sqrt(G*M_sun/r)
    double vy = 0;

    vec pos_earth(2), vel_earth(2), pos_sun(2), vel_sun(2), pos_jup(2), vel_jup(2);

    // Initial conditions
    vel_earth(0) = vx; vel_earth(1) = vy; pos_earth(0) = 0; pos_earth(1) = r;
    vel_jup(0) = 0; vel_jup(1) = 2.889; pos_jup(0) = 5.2; pos_jup(1) = 0;
    vel_sun.fill(0); pos_sun.fill(0);

    string dt_string = static_cast<ostringstream*>(&(ostringstream() << dt) )->str();
    string time_string = static_cast<ostringstream*>(&(ostringstream() << T) )->str();
    //string string_v = static_cast<ostringstream*>(&(ostringstream() << vx) )->str();

    celestialbodies sun("Sun", 1., pos_sun, vel_sun);
    celestialbodies earth("Earth", 3e-6, pos_earth, vel_earth);
    celestialbodies jupiter("Jupiter", 0.0009546, pos_jup, vel_jup); //0.0009546

    solarsystem MySolarsystem_verlet(dt, "three-body_verlet_"+time_string+"yr_"+dt_string);
    solarsystem MySolarsystem_RK4(dt, "three-body_RK4_"+time_string+"yr_"+dt_string);

    MySolarsystem_verlet.AddObject(&sun);
    MySolarsystem_verlet.AddObject(&earth);
    MySolarsystem_verlet.AddObject(&jupiter);

    MySolarsystem_RK4.AddObject(&sun);
    MySolarsystem_RK4.AddObject(&earth);
    MySolarsystem_RK4.AddObject(&jupiter);

    for(j=0; j<n; j++){

        // Print progress.
        if (j % (n/100) == 0 && n > 999) {
            printf("Progress: %5.1f %% \r", 100*j/ ((double) n));
            fflush(stdout);
        }

        MySolarsystem_verlet.verlet(j);
    }
    cout << "Completed Verlet Procedure" << endl;



    // Fourth order Runge-Kutta:
    for(j=0; j<n; j++){

        // Print progress.
        if (j % (n/100) == 0 && n > 999) {
            printf("Progress: %5.1f %% \r", 100*j/ ((double) n));
            fflush(stdout);
        }

        MySolarsystem_RK4.RK4();
    }
    cout << "Completed RK4 Procedure" << endl;
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
