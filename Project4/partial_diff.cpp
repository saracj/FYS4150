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
    C = zeros<mat>(nx-2,nx-2);

    C.diag(-1) += -1; C.diag() += 2;  C.diag(1) += -1;

}


// Solves time evolution of the diffusion equation
// using the Explicit scheme
mat partial_diff::EXPLICIT(mat u){

    A = eye<mat>(nx-2,nx-2) - alpha*C;

    for(int j=0; j<nt-1; j++){
        u.row(j+1) = (A*u.row(j).t()).t();
    }

    return u;
}


mat partial_diff::IMPLICIT(mat u){
    // Solves the diffusion equation using the implicit method

    A = eye<mat>(nx-2,nx-2) + alpha*C;

    for(int j=0; j<nt-1; j++){
        U = solve(A, u.row(j).t()); // Temporary (?)
        //U = TRIDIAG(u.row(j).t(), A); // This one doesn't work, need to fix
        u.row(j+1) = U.t();
    }
    return u;
}


mat partial_diff::CRANK_NICOLSON(mat u){
    // Solves time evolution using the Crank-Nicolson scheme

    A1 = 2*eye<mat>(nx-2,nx-2) - alpha*C;
    A2 = 2*eye<mat>(nx-2,nx-2) + alpha*C;

    for(int j=0; j<nt-1; j++){
        u_temp = A1*u.row(j).t();  // Temporary vector
        // V = TRIDIAG(v_temp, A2);
        U  = solve(A2, u_temp);
        u.row(j+1) = U.t();
    }
    cout << size(u) << endl;
    return u;
}





vec partial_diff::TRIDIAG(vec V_prev, mat A){
    // A tridiagonal matrix system A \vec{x} = B, where A and B are matrices
    F = zeros<vec>(nx-2); B = zeros<vec>(nx-2); V = zeros<vec>(nx-2);
    a = zeros<vec>(nx-2); b = zeros<vec>(nx-2); c = zeros<vec>(nx-2);

    for(int i=0; i<nx-3; i++){
        a(i) = A.diag(-1)(i);
        c(i) = A.diag(1)(i);
    }

    b = A.diag();
    a(nx-3) = A.diag(-1)(0);
    c(nx-3) = A.diag(1)(0);


    // Calculates vecotrs containing the factors f' and b'
    F(0) = V_prev(0);
    B(0) = b(0);


    for(int i=1; i<nx-2; i++){
        factor = (a(i)*B(i-1));
        B(i) = b(i) - factor*c(i-1);
        F(i) = V_prev(i) - factor*F(i-1);
    }


    V(nx-3) = F(nx-3)/B(nx-3);
    for(int i=nx-4; i>=0; i--){
        V(i) = (F(i) - c(i)*V(i+1))/B(i);
    }

    return V;
}

void partial_diff::setU(mat new_u){ this->u = new_u; }
mat partial_diff::getU(){ return this->u; }
