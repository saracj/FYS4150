#include <iostream>
#include <armadillo>
#include <cmath>
#include "solarsystem.h"
#include "celestialbodies.h"

using namespace std;
using namespace arma;

int main(){

    int j;
    int n = 100000; // number of steps

    double r = 1.; // Distance from earth to sun [AU]
    double G = 4*M_PI*M_PI; // Gravitational constant [Au^3 yr^-2 M_sun^-1]
    double T = 50.; // end time of simulation [years]
    double dt = T/n; // time step, [years]
    double vx = 6.28616;// v^2 * r = G*M_sun -- v = sqrt(G*M_sun/r)
    double vy = 0;

    vec pos_earth(2), vel_earth(2), pos_sun(2), vel_sun(2), pos_jup(2), vel_jup(2);
    vec pos_merc(2), pos_ven(2), pos_mar(2), pos_sat(2), pos_ur(2), pos_nep(2);
    vec vel_merc(2), vel_ven(2), vel_mar(2), vel_sat(2), vel_ur(2), vel_nep(2);

    // Initial conditions
    vel_sun(0) = -1.886e-5; vel_sun(1) = -2.757e-3;     pos_sun.fill(0);
    vel_merc(0) = 0;        vel_merc(1) = 9.99088356;   pos_merc(0) = 0.387;    pos_merc(1) = 0;
    vel_ven(0) = 0;         vel_ven(1) = 7.38729464;    pos_ven(0) = 0.722;     pos_ven(1) = 0;
    vel_earth(0) = vx;      vel_earth(1) = vy;          pos_earth(0) = 0;       pos_earth(1) = r;
    vel_mar(0) = 0;         vel_mar(1) = 5.07892327;    pos_mar(0) = 1.52;      pos_mar(1) = 0;
    vel_jup(0) = 0;         vel_jup(1) = 2.889;         pos_jup(0) = 5.2;       pos_jup(1) = 0;
    vel_sat(0) = 0;         vel_sat(1) = 2.0419478;     pos_sat(0) = 9;         pos_sat(1) = 0;
    vel_ur(0) = 0;          vel_ur(1) = 1.43442614;     pos_ur(0) = 19.2;       pos_ur(1) = 0;
    vel_nep(0) = 0;         vel_nep(1) = 1.14543146;    pos_nep(0) = 30.1;      pos_nep(1) = 0;


    string dt_string = static_cast<ostringstream*>(&(ostringstream() << dt) )->str();
    string time_string = static_cast<ostringstream*>(&(ostringstream() << T) )->str();
    //string string_v = static_cast<ostringstream*>(&(ostringstream() << vx) )->str();

    celestialbodies sun("Sun", 1., pos_sun, vel_sun);
    celestialbodies mercury("Mercury", 1.65956463e-7, pos_merc, vel_merc);
    celestialbodies venus("Venus", 2.44699613e-6, pos_ven, vel_ven);
    celestialbodies earth("Earth", 3e-6, pos_earth, vel_earth);
    celestialbodies mars("Mars", 3.22604696e-7, pos_mar, vel_mar);
    celestialbodies jupiter("Jupiter", 0.0009546, pos_jup, vel_jup);
    celestialbodies saturn("Saturn", 0.000285716656 , pos_sat, vel_sat);
    celestialbodies uranus("Uranus", 4.36430044e-5, pos_ur, vel_ur);
    celestialbodies neptune("Neptune", 5.14855965e-5, pos_nep, vel_nep);

    solarsystem MySolarsystem_verlet(dt, "solarsystem_verlet_"+time_string+"yr_"+dt_string);
    solarsystem MySolarsystem_RK4(dt, "solarsystem_RK4_"+time_string+"yr_"+dt_string);

    MySolarsystem_verlet.AddObject(&sun);
    MySolarsystem_verlet.AddObject(&mercury);
    MySolarsystem_verlet.AddObject(&venus);
    MySolarsystem_verlet.AddObject(&earth);
    MySolarsystem_verlet.AddObject(&mars);
    MySolarsystem_verlet.AddObject(&jupiter);
    MySolarsystem_verlet.AddObject(&saturn);
    MySolarsystem_verlet.AddObject(&uranus);
    MySolarsystem_verlet.AddObject(&neptune);

    MySolarsystem_RK4.AddObject(&sun);
    MySolarsystem_RK4.AddObject(&mercury);
    MySolarsystem_RK4.AddObject(&venus);
    MySolarsystem_RK4.AddObject(&earth);
    MySolarsystem_RK4.AddObject(&mars);
    MySolarsystem_RK4.AddObject(&jupiter);
    MySolarsystem_RK4.AddObject(&saturn);
    MySolarsystem_RK4.AddObject(&uranus);
    MySolarsystem_RK4.AddObject(&neptune);

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
