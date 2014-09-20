#include <iostream>
#include <armadillo>
#include <cmath>
#include <jacobi.cpp>
#include "time.h"

int main(){
    // int n = atoi(argv[1]);
    int n = 275;
    double N = (double) n;
    double rho_max = 10.;
    double rho_min = 0.;
    double h = (rho_max - rho_min)/N;
    double TIME1, TIME2;

    // Timing the two methods:
    clock_t start, finish, start2, finish2; // Declare start and finish time

    vec rho(n), V(n);
    for(int i=0; i<n; i++){
        rho[i] = rho_min + (i+1)*h;
        V[i] = rho[i]*rho[i];
    }

    //Initializes the matrix A:
    mat A = zeros<mat>(n,n);
    A.diag(-1) += -1./(h*h);
    A.diag(+1) += -1./(h*h);
    A.diag() = (2./(h*h)) + V;

    // Initial nxn eigenvector matrix using the .diag
    // function from armdillo:
    mat R = eye<mat>(n,n);

    // Built in eigenvalue/eigenvector procedure in armadillo:

    mat eigvec;
    vec eigval;
    start2 = clock();
    eig_sym(eigval, eigvec, A);
    finish2 = clock();

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
    cout << "computation time for jacobi.cpp with n = " << n << ": " << TIME1 << endl;
    cout << "computation time for built in procedure with n = " << n << ": " << TIME2 << endl;


    /*
    // Constant for analytical solution:
    m = ; // electron mass
    h_bar = ; // Reduced Planck constant
    k =
    // Checking agains analytical solution for eigenvalues:
    alpha = pow((h_bar*h_bar/(m*k)), 0.25);
    lambda = 2.*m*alpha*alpha*E/(h_bar*h_bar);
    */

    return 0;
}
