#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main()
{
    int N  = 1e4;        // Number of particles at x0
    int nx = 100;        // Number of position steps/''boxes''
    vector<double> u(nx); // contains the coordinates of the particles

    double dt = 1e-3;     // Time step
    double t_end = 3;    // Final simulation time
    int    nt = t_end/dt; // Number of time steps

    double D  = 1.;            // Diffusion coefficient
    double l0 = sqrt(2.*D*dt); // Step length
    double d = 1.;             // length of x-interval

    u[0] = N; // Number of part. at x0 = 1e4
    // Counters to check if-tests
    int counter1, counter2, counter3, counter4;
    counter1 = 0; counter2 = 0; counter3 = 0; counter4 = 0;


    for(int j=0; j<nt; j++){
        //cout << "Initial number of particles at t = " << 0 + j*dt << " is N = " << u.size() << endl;
        // The number of particles should remain the same,
        // this is just to make sure.

        // cout << "Number of particles at x0 (should be u(0) = " << N << ") is N_final = " << u[0] << endl;
        int nu = u.size();
        for(int i=(nu-1); i>=0; i--){

            double eps = rand() % 100; eps /= 100;
            double xold = u[i]; double xnew;
            //cout << eps << endl;

            if(eps <= 0.5){xnew = xold - l0;}
            if(eps > 0.5){xnew = xold + l0;}

            // Check the end points:
            if(xnew >= d){
                // Remove if the particle is placed outside of the
                // x interval, 0 to d
                u.erase(u.begin() + i-1);
                counter1 += 1;
            }

            if(xnew > xold && xold == 0.){
                u.push_back(0.);
                counter2 += 1;
            }

            if(xnew <= 0.){
                // reject move if the particle is moved back to x0
                // or behind the x0-line
                u.erase(u.begin() + i-1);
                counter3 += 1;
            }

            else{u[i] = xnew; counter4 += 1;}
        }
    }
    cout << "counter 1 = " << counter1 << endl;
    cout << "counter 2 = " << counter2 << endl;
    cout << "counter 3 = " << counter3 << endl;
    cout << "counter 4 = " << counter4 << endl;

    return 0;
}

