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

    int getNumberOfObj();
    vec getForces(celestialbodies);
    vec acceleration(celestialbodies);
    void AddObject(celestialbodies);
    vec advance(celestialbodies);

private:
    double dt, length, m, M;
    vec k1, k2, k3, k4;
    vec K1, K2, K3, K4;
    vec next;
    double G; // Gravitational constant [Au^3 / yr^2 M_sun]
    int i;
    vec pos, vel, next_pos, next_vel, R, accel;
};

#endif // SOLARSYSTEM_H
