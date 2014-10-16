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
    vec RK4(celestialbodies);
    vec verlet(celestialbodies);

private:
    double dt, length, m, M;
    vec k1, k2, k3, k4;
    vec K1, K2, K3, K4;
    double G; // Gravitational constant [Au^3 / yr^2 M_sun]
    int i;
    vec RK4_next, RK4_pos, RK4_vel, RK4_next_pos, RK4_next_vel, R, accel;
    vec verlet_next_pos, verlet_pos, verlet_vel, verlet_next, previous_pos;
};

#endif // SOLARSYSTEM_H
