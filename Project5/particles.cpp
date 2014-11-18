#include "particles.h"
#include <armadillo>
#include <vector>

using namespace std;
using namespace arma;

particles::particles(double pos){
    this->position = pos;
}

// Updates postion
void particles::setPos(double newPosition){
    this->position = newPosition;
}

double particles::getPos(){ return position; }
