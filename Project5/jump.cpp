#include "jump.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <armadillo>
#include <vector>

using namespace arma;
using namespace std;

jump::jump(int m_dimensions, int m_nt, double m_l0, double m_d){
    this->dim = m_dimensions;
    this->nt = m_nt;
    this->l0 = m_l0;
    this->d  = m_d;

}


void jump::AddParticle(particles *newparticle){
    u.push_back(newparticle);
}


void jump::particle_loop(){
    counter1 = 0; counter2 = 0; counter3 = 0;

    for(int j=0; j<nt; j++){

        nu = getNumberOfParticles();
        for(int i=(nu-1); i>=0; i--){

            eps = rand() % 100; eps /= 100;
            xold = u[i]->getPos();
            // cout << eps << endl;

            left_right(eps, xold, i);
        }
    }

    // If-test counters
    cout << "counter 1 = " << counter1 << endl;
    cout << "counter 2 = " << counter2 << endl;
    cout << "counter 3 = " << counter3 << endl;

}

void jump::left_right(double eps, double xold, int i){

    if(eps <= 0.5){
        xnew = xold - l0;
        if(xnew >= d){
            // Remove if the particle is placed outside of the
            // x interval, 0 to d
            u.erase(u.begin() + i-1);
            counter1++;
        }

        else if(xnew <= 0.){
            // Remove if the particle is placed outside of the
            // x interval, 0 to d
            u.erase(u.begin() + i-1);
            counter1++;
        }

        else if(xnew > xold && xold <= 0.){
            // Keep the number of particles at x0 equal to N
            particles part(0.);
            u.push_back(&part);
            counter2++;
        }

        else{
            u[i]->setPos(xnew);
            counter3++;
        }
    }


    else{
        xnew = xold + l0;

        if(xnew >= d){
            // Remove if the particle is placed outside of the
            // x interval, 0 to d
            u.erase(u.begin() + i-1);
            counter1 += 1;
        }


        else if(xnew <= 0.){
            // Remove if the particle is placed outside of the
            // x interval, 0 to d
            u.erase(u.begin() + i-1);
            counter1 += 1;
        }


        else if(xnew > xold && xold <= 0.){
            // Keep the number of particles at x0 equal to N
            particles part(0.);
            u.push_back(&part);
            counter2 += 1;
        }


        else{
            u[i]->setPos(xnew);
            counter3 += 1;
        }
    }
}



mat jump::getAllPositions(){
    all_pos = zeros<vec>(u.size(),dim);
    nu = getNumberOfParticles();

    for(int i=0; i<nu; i++){
        // 2D:
        // all_pos.row(i) = u[i].getPos();

        // 1D:
        all_pos(i,0) = u[i]->getPos();
        //cout << all_pos(i,0) << endl;
    }
    return all_pos;
}

int jump::getNumberOfParticles(){ return u.size();}
