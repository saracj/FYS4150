#include "jump.h"
#include "gaussiandeviate.cpp"
#include <cmath>
#include <iostream>
#include <fstream>
#include <armadillo>
#include <vector>
#include <typeinfo>
#include <algorithm>

using namespace arma;
using namespace std;

jump::jump(int dimensions, int time_steps, double time_step_length, double diffusion_coeff, double position_interval, int particles_at_x0) :
    D(diffusion_coeff), d(position_interval), dt(time_step_length),
    dim(dimensions), nt(time_steps), N(particles_at_x0),
    counter1(0), counter2(0), counter3(0), counter4(0)
{
tolerance = 1e-10;
l0 = sqrt(2.*D*dt);
stddev = (1./sqrt(2));
}


void jump::particle_loop() {
    counter1 = 0; counter2 = 0; counter3 = 0;


    // Construct u-vector at t = 0:
    for(int k=0; k<=N; k++) {
        particles *part = new particles(0.);
        AddParticle(part);
    }


    long idum = -1; // RNG seed
    for(int j=0; j<nt; j++) {

        if (j % (nt/100) == 0 && nt > 0) {
            printf("Progress: %5.1f %% (%d particles) \r", 100*j/ ((double) nt), u.size());
            fflush(stdout);
        }



        for(int i=(getNumberOfParticles()-1); i>=0; i--) {

            double ksi = stddev*gaussian_deviate (& idum );
            l = sqrt(2.*D*dt)*ksi;
            random_walk(i, l);
            // cout << "ksi = " << ksi << endl;
            //cout << l << endl;


            /*
            // Constant step length, assignment a).
            double eps = rand() % 100; eps /= 100;
            if(eps <= 0.5) { random_walk(i, -l0); } // LEFT
            else{ random_walk(i, l0); } // RIGHT
            */
        }


        // Erase the elements that were moved outside the interval in this time step
        int k_end = erase_indices.size(); // signed-unsigned trouble in loop
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

        /*
        // Check number of particles at x = 0.
        int nzero = 0;
        for(int i=(getNumberOfParticles()-1); i>=0; i--) {
            if(u[i]->getPos() == 0.) { nzero++; }
        }
        cout << "number of particles at x = 0: N = " << nzero << endl;
        */

    }

    // If-test counters:
    cout << "\nParticles erased " << counter1 << " times" << endl;
    cout << "Particles added " << counter2 << " times" << endl;
    cout << "Particles moved " << counter3 << " times" << endl;


    // Write vector to file:
    writeToFile("gaussStepLength", u);
}


void jump::random_walk(int i, double step){
    // INPUT: Particle index -i-, step length -step-
    // Calculates the particles next position from the given step length.
    // Checks if the particle is placed outside the interval and saves this particles
    // index so that it can be removed at the end of this time step.

    double xold = u[i]->getPos();
    double xnew = xold + step;


    if(xnew <= 0. || xnew >= d) {
        // Remove if the particle is placed outside of the x interval, 0 to d
        erase_indices.push_back(i);
        counter1++;
    }
    else {
        u[i]->setPos(xnew);
        counter3++;
    }
}



void jump::histogram(){
    // Creates a makeshift histogram as a printout used to check the results.
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



void jump::writeToFile(string filename, vector<particles*> data){
    // Input: Filenam, vector of data with

    string FileName = "../Project5/Data/Histogram_"+filename+".dat";
    cout << FileName << endl;
    ofstream outFile;


    outFile.open(FileName.c_str(), ios::out);


    for (int i = 0; i < getNumberOfParticles(); i ++) {
        outFile << data[i]->getPos() << endl;
    }


    outFile.close();
}



int jump::getNumberOfParticles() { return u.size();}
void jump::AddParticle(particles *newparticle) { u.push_back(newparticle); }
