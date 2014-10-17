#include "celestialbodies.h"
#include <armadillo>

using namespace arma;
using namespace std;

celestialbodies::celestialbodies(string id, double MASS, vec pos, vec vel){
    // INPUT: id   --> (short) string describing the object, for example by name
    //        MASS --> mass of object
    //        pos  --> Position of object
    //        vel  --> Velocity of object
    this->position = zeros<vec>(2);
    this->velocity = zeros<vec>(2);
    this->position = pos;
    this->velocity = vel;
    this->m = MASS;
    this->ID = id;

}

// Updates postion
void celestialbodies::setPos(vec newPosition){
    position = newPosition;
}

// Updates velocity
void celestialbodies::setVel(vec newVelocity){
    velocity = newVelocity;
}

//Find distance between this and a different object
vec celestialbodies::getDist(celestialbodies other){
    vec dist = other.getPos() - this->getPos();
    return dist;
}

double celestialbodies::getM(){ return m; }
string celestialbodies::getID() { return ID; }
vec celestialbodies::getPos(){ return position; }
vec celestialbodies::getVel(){ return velocity; }
