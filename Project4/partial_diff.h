#ifndef PARTIAL_DIFF_H
#define PARTIAL_DIFF_H

class partial_diff{
private:
    void EXPLICIT(vec u);
    void IMPLICIT();
    void CRANK_NICOLSON();
    void TRIDIAG(mat B);

    vec u;

public:
    partial_diff();


};

#endif // PARTIAL_DIFF_H
