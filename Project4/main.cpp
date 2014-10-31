#include <iostream>
#include <armadillo>
#include <cmath>
#include <fstream>

#include "partial_diff.h"

using namespace arma;
using namespace std;

int main(){
    double  T  =  1.;
    double  d  =  1.;
    double  dx =  1./10;        // Position step.
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


    void WriteToFile(string, vec, vec, vec, double, double);


    // Initial conditions:
    for(int i=0; i<nx-2; i++){
        v.row(0)(i) =  x(i+1) - 1;
    }


    partial_diff explicit_solution(dx, dt, T, d, nx, nt, D);
    partial_diff implicit_solution(dx, dt, T, d, nx, nt, D);
    partial_diff CN_solution(dx, dt, T, d, nx, nt, D);


    // Get the different solutions
    v_expl  =  explicit_solution.EXPLICIT(v); // Explicit method
    v_impl  =  implicit_solution.IMPLICIT(v); // Implicit method
    //v_CN    =  CN_solution.getU(); // Crank-Nicolson method



    // Adding boundary conditions:
    V_expl.col(0)    = zeros<vec>(nt);
    V_expl.col(nx-1) = zeros<vec>(nt);
    V_impl.col(0)    = zeros<vec>(nt);
    V_impl.col(nx-1) = zeros<vec>(nt);
    /*
    V_CN.col(0)      = zeros<vec>(nt);
    V_CN.col(nx-1)   = zeros<vec>(nt);
    */


    for(int i=0; i<nx-2; i++){
        V_expl.col(i+1) = v_expl.col(i);
        V_impl.col(i+1) = v_impl.col(i);
        //V_CN.col(i+1) = v_CN.col(i);
    }

    // Steady state solution:
    for(int j=0; j<nt; j++){
        Us.row(j) = 1 - x.t()/d;
    }


    // Complete solution:
    Uexpl = V_expl + Us;
    Uimpl = V_impl + Us;
    //UCN   = u_CN + Us;
    cout << "hi" << endl;


    // Analytic solution:
    int n = 1000;
    for(int k=1; k<n; k++){
        for(int i=0; i<nx; i++)
            for(int j=0; j<nt; j++){
                u_analytic(j,i) += (-2/(k*M_PI))*sin(k*M_PI*x(i))*exp(-k*k*M_PI*M_PI*t(j));
        }
    }
    u_analytic += Us;

    // Write the numerical and analytic solutions at two different times
    WriteToFile("Explicit", x, Uexpl.row(10).t(), Uexpl.row(190).t(), t(10), t(190));
    WriteToFile("Implicit", x, Uimpl.row(10).t(), Uimpl.row(190).t(), t(10), t(190));
    WriteToFile("Analytic", x, u_analytic.row(10).t(), u_analytic.row(190).t(), t(10), t(190));


    return 0;
}


void WriteToFile(string filename, vec position, vec data1, vec data2, double TimeStep1, double TimeStep2){
     string TimeStep_string1 = static_cast<ostringstream*>(&(ostringstream() << TimeStep1) )->str();
     string TimeStep_string2 = static_cast<ostringstream*>(&(ostringstream() << TimeStep2) )->str();
     string FileName = "../Project4/Data/"+filename+"_t1="+TimeStep_string1+"_t2="+TimeStep_string2+".dat";
     cout << FileName << endl;
     ofstream outFile;

     outFile.open(FileName.c_str(), ios::out);


     int N = data1.n_elem;
     for (int i = 0; i < N; i ++) {
         outFile << position(i) << " " << data1(i) << " " << data2(i) << endl;
     }

     outFile.close();
}
