#include <iostream>
#include <armadillo>
#include <cmath>
#include <fstream>

#include "partial_diff.h"

using namespace arma;
using namespace std;

int main(){
    void WriteToFile(string, vec, vec, vec, double, double);

    double  T  =  1.;
    double  d  =  1.;
    double  dx =  1./100;        // Position step.
    double  dt =  dx*dx*(1./2); // Demanded by stability: dt/dx^2 <= 1/2
    double  D  =  1.;           // Diffusion coefficient
    int     nt =  T/dt;         // Number of time steps
    int     nx =  d/dx;         // Number of position steps

    vec t          =  linspace<vec>(0, T, nt);
    vec x          =  linspace<vec>(0, d, nx);
    mat u_analytic =  zeros<mat>(nt, nx);
    mat v          =  zeros<mat>(nt, nx-2);
    mat v_expl     =  zeros<mat>(nt, nx-2);
    mat v_impl     =  zeros<mat>(nt, nx-2);
    mat v_CN       =  zeros<mat>(nt, nx-2);
    mat Us         =  zeros<mat>(nt, nx);
    mat V_expl     =  zeros<mat>(nt, nx);
    mat V_impl     =  zeros<mat>(nt, nx);
    mat V_CN       =  zeros<mat>(nt, nx);
    mat Uexpl      =  zeros<mat>(nt, nx);
    mat Uimpl      =  zeros<mat>(nt, nx);
    mat UCN        =  zeros<mat>(nt, nx);


    // Initial conditions:
    for(int i=0; i<nx-2; i++){
        v.row(0)(i) =  x(i+1) - 1;
    }


    partial_diff explicit_solution(dx, dt, T, d, nx, nt, D);
    partial_diff implicit_solution(dx, dt, T, d, nx, nt, D);
    partial_diff CN_solution(dx, dt, T, d, nx, nt, D);

    cout << size(t) << endl;
    cout << "time 1: " << t(500) << endl;
    cout << "time 2: " << t(15000) << endl;
    //cout << t << endl;

    // Get the different solutions
    v_expl  =  explicit_solution.EXPLICIT(v); // Explicit method
    v_impl  =  implicit_solution.IMPLICIT(v); // Implicit method
    v_CN    =  CN_solution.CRANK_NICOLSON(v); // Crank-Nicolson method

    for(int i=0; i<nx-2; i++){
        V_expl.col(i+1) = v_expl.col(i);
        V_impl.col(i+1) = v_impl.col(i);
        V_CN.col(i+1) = v_CN.col(i);
    }

    // Steady state solution:
    for(int j=0; j<nt; j++){
        Us.row(j) = 1 - x.t()/d;
    }


    // Complete solution:
    Uexpl = V_expl + Us;
    Uimpl = V_impl + Us;
    UCN   = V_CN + Us;

    // Analytic solution:
    int n = 500;
    for(int k=1; k<n; k++){
        for(int i=0; i<nx; i++)
            for(int j=0; j<nt; j++){
                u_analytic(j,i) += (-2/(k*M_PI))*sin(k*M_PI*x(i))*exp(-k*k*M_PI*M_PI*t(j));

                }
                if (k % (n/100) == 0 && n > 5) {
                    printf("Progress, analytical solution: %5.1f %% \r", 100*k/ ((double) n));
                    fflush(stdout);
        }
    }
    u_analytic += Us;
    // Write the numerical and analytic solutions at two different times
    WriteToFile("Explicit", x, Uexpl.row(500).t(),      Uexpl.row(15000).t(),      t(10), t(190));
    WriteToFile("Implicit", x, Uimpl.row(500).t(),      Uimpl.row(15000).t(),      t(10), t(190));
    WriteToFile("CN",       x, UCN.row(500).t(),        UCN.row(15000).t(),        t(10), t(190));
    WriteToFile("Analytic", x, u_analytic.row(500).t(), u_analytic.row(15000).t(), t(10), t(190));


    return 0;
}


void WriteToFile(string filename, vec position, vec data1, vec data2, double TimeStep1, double TimeStep2){
     string TimeStep_string1 = static_cast<ostringstream*>(&(ostringstream() << TimeStep1) )->str();
     string TimeStep_string2 = static_cast<ostringstream*>(&(ostringstream() << TimeStep2) )->str();
     string FileName = "../Project4/Data/"+filename+".dat";
     cout << FileName << endl;
     ofstream outFile;

     outFile.open(FileName.c_str(), ios::out);


     int N = data1.n_elem;
     for (int i = 0; i < N; i ++) {
         outFile << position(i) << " " << data1(i) << " " << data2(i) << endl;
     }

     outFile.close();
}
