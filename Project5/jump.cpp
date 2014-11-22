#include "jump.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <armadillo>
#include <vector>
#include <typeinfo>
#include <algorithm>

using namespace arma;
using namespace std;

jump::jump(int m_dimensions, int m_nt, double m_l0, double m_d, int N) :
    l0(m_l0), d(m_d), dim(m_dimensions), nt(m_nt), N(N),
    counter1(0), counter2(0), counter3(0), counter4(0)
{
tolerance = 1e-5;
}


void jump::AddParticle(particles *newparticle){
    u.push_back(newparticle);
}


void jump::particle_loop() {
    counter1 = 0; counter2 = 0; counter3 = 0;

    // Construct u-vector at t = 0:
    for(int k=0; k<=N; k++){
        particles *part = new particles(0.);
        AddParticle(part);
    }

    for(int j=0; j<nt; j++) {

        if (j % (nt/100) == 0 && nt > 0) {
            printf("Progress: %5.1f %% (%d particles) \r", 100*j/ ((double) nt), u.size());
            fflush(stdout);
        }

        int nzero = 0;
        for(int i=(getNumberOfParticles()-1); i>=0; i--) {
            double eps = rand() % 100; eps /= 100;
            left_right(eps, i);
            if(u[i]->getPos() <= tolerance && u[i]->getPos() >= -tolerance) { nzero++; }
        }
        //cout << "number of particles in x = 0: N = " << nzero << " at t = " << nt*j << endl;


        // Erase the elements that were moved outside the interval in this time step
        int k_end = erase_indices.size();
        for(int k=0; k<k_end; k++) {
            int indexToBeRemoved = erase_indices[k];
            swap(u[indexToBeRemoved], u.back());
            u.pop_back();
        }
        erase_indices.clear();



        //Rese number of particles at 0 to N
        for(int k=0; k<N; k++){
            particles *part = new particles(0.);
            AddParticle(part);
            counter2++;
        }

    }

    // If-test counters
    cout << "particles erased " << counter1 << " times" << endl;
    cout << "Particles added " << counter2 << " times" << endl;
    cout << "Particles moved " << counter3 << " times" << endl;
}


void jump::left_right(double eps, int i) {
    double xold = u[i]->getPos();

    if(eps <= 0.5) { // LEFT
        double xnew = xold - l0;

        if(xnew <= tolerance) {
            // Remove if the particle is placed outside of the x interval, 0 to d
            erase_indices.push_back(i);
            counter1++;
        }
        else {
            u[i]->setPos(xnew);
            counter3++;
        }
    }
    else { // RIGHT
        double xnew = xold + l0;

        if(xnew > d) {
            // Remove if the particle is placed outside of the x interval, 0 to d
            erase_indices.push_back(i);
            counter1++;
        }
        else {
            u[i]->setPos(xnew);
            counter3++;
        }
    }
}


void jump::histogram(){
    double nx = 100., x0 = 0., dx = (d - x0)/nx;
    vector<int> box(nx, 0);

    for(int i=0; i<getNumberOfParticles(); i++) {
        double pos = u[i]->getPos();

        for(int n=1; n<=nx; n++) {
            if(pos >= dx*(n-1) && pos < dx*n){ box[n-1] += 1; }
        }
    }

    cout << "Histogram: " << endl;

    int nbox =  box.size();
    for(int i=0; i<=nbox; i++) {
        if(box[i] != 0.) { cout << box[i]  << " particles in [" << dx*i << ", " << dx*(i+1) << "]" << endl; }
        //else { cout << "Box " << i << " is empty" << endl;}
    }
}


int jump::getNumberOfParticles(){ return u.size();}
