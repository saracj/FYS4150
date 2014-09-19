#include <iostream>
#include <armadillo>
#include <cmath>
#include <jacobi.cpp>

int main(){
    // int n = atoi(argv[1]);
    int n = 100;
    double N = (double) n;
    double rho_max = 10.;
    double rho_min = 0.;
    double h = (rho_max - rho_min)/N;

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
mat R = zeros<mat>(n,n);
R.diag() += 1;
Jacobi(A, R, n);

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
