#include <iostream>
#include <armadillo>
#include <cmath>
#include <jacobi.cpp>
#include <fstream>
#include <string>
#include <sstream>
#include "time.h"

ofstream ofile;

int main(){
    int n = 200;
    double N = (double) n;
    double rho_max = 10.;
    double rho_min = 0.;
    double h = (rho_max - rho_min)/N;
    double omega_r = 1.;
    double TIME1, TIME2;
    vec rho(n), V(n-2), eigval;
    mat A = zeros<mat>(n-2,n-2);
    mat eigvec;

    clock_t start, finish, start2, finish2; // Declare start and finish time
    for(int i=1; i<n-1; i++){
        rho[i] = rho_min + (i+1)*h;
        V[i] = omega_r*omega_r*rho[i]*rho[i] + 1./rho[i];
        }
    rho[0] = 0.;
    rho[n-1] = rho_max;

    //Initializes the matrix A:
    A.diag(-1) += -1./(h*h);
    A.diag(+1) += -1./(h*h);
    A.diag() = (2./(h*h)) + V;

    // Eigenvector matrix:
    mat R = eye<mat>(n-2,n-2);

    // Built in eigenvalue/eigenvector procedure in armadillo:
    start2 = clock();
    eig_sym(eigval, eigvec, A);
    finish2 = clock();

    // Jacobi method:
    start = clock();
    Jacobi(&A, &R, (n-2));
    finish = clock();

    TIME1 = (finish - start)/(double)CLOCKS_PER_SEC;
    TIME2 = (finish2 - start2)/(double)CLOCKS_PER_SEC;

    vec l;
    l = A.diag();

    // Wavefunction for the lowest energy level:

    double MIN = max(l);
    int index = 0;
    for(int i=0; i<n-2; i++){
        if(l(i) <= MIN){
            MIN = l(i);
            index = i;
        }
    }

    vec u_1 = R.col(index);
    vec wave(n);
    for(int i=1; i<n-1; i++){
        wave(i) = u_1(i-1);
    }

    // Dirichlet boundary conditions
    wave(0) = 0;
    wave(n-1) = 0;

    //Writing wave and rho to file:
    string filename;
    string Omega = static_cast<ostringstream*>( \
                &(ostringstream() << omega_r*100) )->str();
    filename = "wavefunc2_omega"+Omega+".dat";

    ofile.open(filename.c_str(), ios::out);
    for(int i=0; i<n; i++){ ofile << rho[i] << ' ' << wave[i] << endl; }
    ofile.close();

    vec lam = sort(l);
    cout << "omega_r = " << omega_r << endl;
    cout << "three lowest eigenvalues:" << endl;
    for(int i=0;i<3;i++){
        cout << "lambda = " << lam(i) << endl;
    }

    cout << "computation time for jacobi.cpp with n = " << n << ": " << TIME1 << " s" << endl;
    cout << "computation time for built in procedure with n = " << n << ": " << TIME2 << " s" << endl;

    return 0;
}
