#ifndef PARTIAL_DIFF_H
#define PARTIAL_DIFF_H
#include <iostream>
#include <armadillo>
#include <cmath>

class partial_diff{
private:
    arma::vec TRIDIAG(arma::vec V_prev, arma::mat derivation_matrix);
    void setU(arma::mat new_u);

    double dx, dt, d, T, D;

    double alpha;
    int nx, nt;
    arma::mat u, A, C;

    // Tridiag function:
    double factor;
    arma::vec F, B, f, b, c, a, V, V_prev, U;


public:
    partial_diff(double position_step, double time_step, double end_time, double end_position, int position_steps, int time_steps, double D);
    arma::mat IMPLICIT(arma::mat u);
    arma::mat CRANK_NICOLSON(arma::mat u);
    arma::mat EXPLICIT(arma::mat u);
    arma::mat getU();


};

#endif // PARTIAL_DIFF_H
