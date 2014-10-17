#ifndef CELESTIALBODIES_H
#define CELESTIALBODIES_H
#include <armadillo>

using namespace arma;
using namespace std;

class celestialbodies{
private:
    vec position, velocity, force;
    double m;
    string ID;

public:
    celestialbodies(string id, double mass, vec pos, vec vel);

    double getM();
    string getID();
    vec getPos(), getVel();
    vec getDist(celestialbodies);

    void setPos(vec), setVel(vec);
};

#endif // CELESTIALBODIES_H
