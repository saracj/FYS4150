#include "jump.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <armadillo>
#include <vector>
#include <typeinfo>

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

    for(int j=0; j<100; j++){

        if (j % (nt/100) == 0 && nt > 0) {
            printf("Progress: %5.1f %% \r", 100*j/ ((double) nt));
            //fflush(stdout);
        }


        nu = getNumberOfParticles();
        //cout << j << endl;
        for(int i=(nu-1); i>=0; i--){
            eps = rand() % 100; eps /= 100;
            left_right(eps, i);
            printf("particle position, x = %2.5f \r", u[i]->getPos());
        }

        // Erase the elements that were moved outside
        // the interval in this time step.
        k_end = erase_indices.size();
        for(int k=0; k<(k_end- 1 ); k++){
            u.erase(u.begin() + (erase_indices[k]-1));
        }
        //printf("Number of elements in u: N_tot = %i at n_t = %i \n", u.size(), j);
        erase_indices.clear();
    }

    // If-test counters
    cout << "counter 1 = " << counter1 << endl;
    cout << "counter 2 = " << counter2 << endl;
    cout << "counter 3 = " << counter3 << endl;
}


void jump::left_right(double eps, int i){
    xold = u[i]->getPos();

    /*
    if(xold > 0.){
        printf("xold = %5.6f at n_x = %i \n", xold, i);
    }
    */

    if(eps <= 0.5){
        xnew = xold - l0;

        if(xnew <= 0.){
            // Remove if the particle is placed outside of the
            // x interval, 0 to d
            erase_indices.push_back(i);
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
            //printf("position updated at i = %i \n", i);
        }
    }


    else{
        xnew = xold + l0;

        if(xnew >= d){
            // Remove if the particle is placed outside of the
            // x interval, 0 to d
            erase_indices.push_back(i);
            counter1++;
        }

        else if(xnew > xold && xold == 0.){
            // Keep the number of particles at x0 equal to N
            particles part(0.);
            u.push_back(&part);
            counter2++;
        }


        else{
            u[i]->setPos(xnew);
            counter3++;
            //printf("position updated at i = %i \n", i);
        }
    }
}



mat jump::getAllPositions(){
    nu = getNumberOfParticles();
    all_pos = zeros<mat>(nu, dim);

    for(int i=0; i<nu; i++){
        for(int k=0; k<dim; k++){
            pos = u[i]->getPos();
            all_pos(i,k) = pos;
            printf("particle position, x = %2.5f \r", u[i]->getPos());
        }
    }
    return all_pos;
}

int jump::getNumberOfParticles(){ return u.size();}
