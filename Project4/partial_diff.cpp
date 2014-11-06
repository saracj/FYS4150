#include <armadillo>
#include "partial_diff.h"

using namespace arma;
using namespace std;

partial_diff::partial_diff(double position_step, double time_step, double end_time, double end_position, int position_steps, int time_steps, double D){
    this->dx = position_step;   // Position step length
    this->dt = time_step;       // Time step length
    this->T = end_time;
    this->d = end_position;
    this->nx = position_steps;
    this->nt = time_steps;
    this->D = D; // Diffusion coeffictient
    this->alpha = this->D*dt/(dx*dx);

    A = zeros<mat>(nx-2,nx-2);
    B = zeros<mat>(nx-2,nx-2);

    B.diag(-1) += -1; B.diag() += 2;  B.diag(1) += -1;

}


// Solves time evolution of the diffusion equation
// using the Explicit scheme
mat partial_diff::EXPLICIT(mat u){
    // Should change all these methods to element-wise calculations,
    // instead of matrix multiplications, in order to save computation
    // time.....
    A = eye<mat>(nx-2,nx-2) - alpha*B;

    for(int j=0; j<nt-1; j++){
        u.row(j+1) = (A*u.row(j).t()).t();
    }

    return u;
}


mat partial_diff::IMPLICIT(mat u){
    // Solves the diffusion equation using the implicit method

    A = eye<mat>(nx-2,nx-2) + alpha*B;

    for(int j=0; j<nt-1; j++){
        //U = solve(A, u.row(j).t());
        U = TRIDIAG(u.row(j).t(), A);
        u.row(j+1) = U.t();
    }
    return u;
}


mat partial_diff::CRANK_NICOLSON(mat u){
    // Solves time evolution using the Crank-Nicolson scheme

    A1 = 2*eye<mat>(nx-2,nx-2) - alpha*B;
    A2 = 2*eye<mat>(nx-2,nx-2) + alpha*B;

    for(int j=0; j<nt-1; j++){
        u_temp = A1*u.row(j).t();  // Temporary vector
        //U  = solve(A2, u_temp);
        U = TRIDIAG(u_temp, A2);
        u.row(j+1) = U.t();
    }
    return u;
}



vec partial_diff::TRIDIAG(vec f, mat A){
    // A tridiagonal matrix system A \vec{v} = \vec{f}, where A is a matrix
    int n = nx-2;
    v = zeros<vec>(n); ftemp = zeros<vec>(n); btemp = zeros<vec>(n);
    a = zeros<vec>(n); b = zeros<vec>(n); c = zeros<vec>(n);

    a(0) = 0;
    c(n-1) = 0;
    b = A.diag();

    for(int i=0; i<n-1; i++){
        a(i+1) = A.diag(-1)(i);
        c(i) = A.diag(1)(i);
    }


    // Forward substitution:

    btemp(0) = b(0);
    ftemp(0) = f(0);

    for(int i=1; i<=n-1; i++){
        factor = a(i)/btemp(i-1);
        btemp(i) = b(i) - factor*c(i-1);
        ftemp(i) = f(i) - factor*ftemp(i-1);
    }


    // Bacward substitution:

    v(n-1) = ftemp(n-1)/btemp(n-1);

    for(int i=n-2; i>=0; i--){
        v(i) = (ftemp(i) - c(i)*v(i+1))/btemp(i);
    }

    return v;
}

void partial_diff::setU(mat new_u){ this->u = new_u; }
mat partial_diff::getU(){ return this->u; }
