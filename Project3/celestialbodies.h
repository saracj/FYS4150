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
    celestialbodies(string, double, vec, vec);

    double getM();
    string getID();
    vec getPos(), getVel(), getForce();
    vec getDist(celestialbodies);

    void setPos(vec), setVel(vec), setF(vec);
};

#endif // CELESTIALBODIES_H
