#ifndef PARTIAL_DIFF_H
#define PARTIAL_DIFF_H

class partial_diff{
private:
    void EXPLICIT(vec u);
    void IMPLICIT();
    void CRANK_NICOLSON();
    void TRIDIAG(mat B);

    double dx, dt, d, T, D; // Constructor
    int nx, nt; // Constructor

    double C; // EXPLICIT

public:
    partial_diff(double position_step, double end_time, double end_position, double D);


};

#endif // PARTIAL_DIFF_H
