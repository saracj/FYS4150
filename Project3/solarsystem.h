#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#include <armadillo>

class solarsystem{

public:
    solarsystem();
    vec acceleration;
    vec position;
    vec velocity;

private:
    double dt;
    vec force();


};

#endif // SOLARSYSTEM_H
