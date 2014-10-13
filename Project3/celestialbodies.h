#ifndef CELESTIALBODIES_H
#define CELESTIALBODIES_H
#include <armadillo>

using namespace arma;
using namespace std;

class celestialbodies{
private:
    vec position, velocity, force;
    double m;
    string id;

public:
    celestialbodies(string id, double MASS, vec pos, vec vel);

    double getM();
    string getID();
    vec getPos(), getVel(), getForce();
    vec getDist(celestialbodies);

    void setPos(vec newPosition), setVel(vec newVelocity), setF(vec newForce);
};

#endif // CELESTIALBODIES_H
