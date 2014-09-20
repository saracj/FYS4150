#include <iostream>
#include <armadillo>
#include <cmath>
#include <jacobi.cpp>
#include "time.h"

int main(){
    // int n = atoi(argv[1]);
    int n = 100;
    double N = (double) n;
    double rho_max = 10.;
    double rho_min = 0.;
    double h = (rho_max - rho_min)/N;
    double omega_r = 0.01;
    double TIME1, TIME2;
    vec rho(n), V(n), eigval;
    mat A = zeros<mat>(n,n);
    mat eigvec;

    // Timing the two methods:
    clock_t start, finish, start2, finish2; // Declare start and finish time
    for(int i=0; i<n; i++){
        rho[i] = rho_min + (i+1)*h;
        V[i] = omega_r*rho[i]*rho[i] + 1./rho[i];
        }

    //Initializes the matrix A:
    A.diag(-1) += -1./(h*h);
    A.diag(+1) += -1./(h*h);
    A.diag() = (2./(h*h)) + V;

    // Eigenvector matrix:
    mat R = eye<mat>(n,n);

    // Built in eigenvalue/eigenvector procedure in armadillo:
    start2 = clock();
    eig_sym(eigval, eigvec, A);
    finish2 = clock();

    // Jacobi method:
    start = clock();
    Jacobi(&A, &R, n);
    finish = clock();

    //A.print("Transformed matrix: ");
    //R.print("Eigenvector matrix: ");

    vec lambda = sort(A.diag());

    TIME1 = (finish - start)/(double)CLOCKS_PER_SEC;
    TIME2 = (finish2 - start2)/(double)CLOCKS_PER_SEC;

    //cout << "jacobi.cpp gives: " << endl;
    //lambda.print("lambda = ");
    //cout << "Built in eigenvalue procedure in armadillog gives:" << endl;
    //eigval.print("lambda_armadillo = ");

    cout << "The three first eigenvalues for \omega_r = " << omega_r << " with n = " << n << ":" << endl;
    cout << lambda(0) << endl;
    cout << lambda(1) << endl;
    cout << lambda(2) << endl;
    cout << "computation time for jacobi.cpp with n = " << n << ": " << TIME1 << " s" << endl;
    cout << "computation time for built in procedure with n = " << n << ": " << TIME2 << " s" << endl;

    return 0;
}
