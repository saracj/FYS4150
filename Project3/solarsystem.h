#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#include <armadillo>
#include "celestialbodies.h"

class solarsystem{

public:
    solarsystem();
    vec position;
    vec velocity;
    vector<celestialbodies> objects;

    int getNumberOfObjects();
    vec getForces(celestialbodies);
    vec acceleration(celestialbodies);
    void AddObject(celestialbodies);
    void advance(celestialbodies, mat*, mat*, int);

private:
    double dt, length, R, m, M;
    double k1, k2, k3, k4;
    double K1, K2, K3, K4;
    double G; // Gravitational constant [Au^3 / yr^2 M_sun]
    int i;
    vec pos, vel, next_pos, next_vel;



};

#endif // SOLARSYSTEM_H
