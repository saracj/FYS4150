#include <iostream>
#include <armadillo>
#include <cmath>

using namespace std;
using namespace arma;

void Jacobi(mat * B, mat * S, int n){
    /* Jacobi's method --> transformation by
    * rotation in a plane*/

    double max_it = (double)n*(double)n*(double)n;
    double eps = 1.0e-10;
    int k, l;
    double c, s;

    mat A = *B;
    mat R = *S;

    // Function declaration:
    double max_offdiag(mat A, int n, int * k, int * l);
    mat rotation_matrix(mat A, int k, int l, int n, double * c, double * s);
    mat eigenvector(mat R, int n, int k, int l, double c, double s);

    double MAX = max_offdiag(A, n, &k, &l);
    int counter = 0;
    while ( fabs(MAX) > eps ){
        if( counter >= max_it){
            break;
            cout << "Reached the maximum number of iterations!" << endl;
        }
        MAX = max_offdiag(A, n, &k, &l);
        A = rotation_matrix(A, k, l, n, &c, &s);
        R = eigenvector(R, n, k, l, c, s);
        counter += 1;
    }

    *B = A;
    *S = R;

    cout << "Number of iterations: " << counter << endl;
    return;
}

double max_offdiag(mat A, int n, int * k, int * l){
    /* Finds the maximum value of a off-diagonal
    * element and returns both the max value
    * and the element's indices. We do this in order to
    * minimize the problem that the jaobi method may
    * set a (i,l)-element not equal to zero in the
    * transformation. */

    double MAX = 0.0;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if( fabs(A(i, j)) > MAX){
                MAX = fabs(A(i, j));
                *k = i;
                *l = j;
            }
        }
    }
return MAX;
}

mat rotation_matrix(mat A, int k, int l, int n, double * c, double * s){
    /* Finds the values for the index
    * (k,l) in the rotation matrix and
    * calculates cos() and sin() from
    * the equations given in the
    * lecture notes and transforms the
    * matrix using the values for
    * c and s */

    // s = sin(theta), c = cos(theta)
    double a_kk, a_ll, a_kl, a_ik, a_il;

    if(A(k, l) != 0){
        double t, tau;
        tau = (A(l,l) - A(k,k))/(2.*A(k, l));
        /* Choosing the smaller of the roots will guarantee
         * that the difference between the two matrices is
         * minimal. The factor in front of the sum becomes
         * as small as possible */
        if(tau >= 0.0){
            t = 1.0/(tau + sqrt(1.0 + tau*tau));
        }
        else{
            t = -1.0/(-tau + sqrt(1.0 + tau*tau));
        }

        *c = 1./sqrt(1 + t*t);
        *s = (*c)*t;
    }
    else{ //theta = 0
        *c = 1.0;
        *s = 0.0;
    }

    /* Changing matrix elements with the equations
    * from the lecture notes, topp of page 216.*/
    a_kk = A(k, k);
    a_ll = A(l, l);
    a_kl = A(k, l);
    A(k, k) = a_kk*(*c)*(*c) - 2.0*(*c)*(*s)*a_kl + a_ll*(*s)*(*s);
    A(l, l) = a_ll*(*c)*(*c) + 2.0*(*c)*(*s)*a_kl + a_kk*(*s)*(*s);
    A(k, l) = 0.0; // Require the non-diagonal matrix elements to
    A(l, k) = 0.0; // be zero in the 2x2 diagonalization.

    // Iterate over the remaining matrix elements:
    for(int i=0; i<n; i++){
        if( (i != k) && (i != l)){
            a_ik = A(i, k);
            a_il = A(i, l);
            A(i, k) = a_ik*(*c) - a_il*(*s);
            A(i, l) = a_il*(*c) + a_ik*(*s);
            A(k, i) = A(i, k);
            A(l, i) = A(i, l);
        }
    }
    return A;
}

mat eigenvector(mat R, int n, int k, int l, double c, double s){
    double r_ik, r_il;

    for(int i=0; i<n; i++){
        r_ik = R(i, k);
        r_il = R(i, l);
        // New eigen vectors:
        R(i, k) = c*r_ik - s*r_il;
        R(i, l) = c*r_il + s*r_ik;
    }
    return R;
}
