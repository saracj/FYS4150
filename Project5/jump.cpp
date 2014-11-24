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

jump::jump(int dimensions, int time_steps, double time_step_length, double position_step_length, double diffusion_coeff, double position_interval, int particles_at_x0) :
    D(diffusion_coeff), d(position_interval), l0(position_step_length), dt(time_step_length),
    dim(dimensions), nt(time_steps), N(particles_at_x0),
    counter1(0), counter2(0), counter3(0), counter4(0)
{
tolerance = 1e-10;
l0 = sqrt(2.*D*dt);
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


    // Setting up normal distribution of random numbers:
    double stddev = 1./sqrt(2);



    for(int j=0; j<nt; j++) {

        if (j % (nt/100) == 0 && nt > 0) {
            printf("Progress: %5.1f %% (%d particles) \r", 100*j/ ((double) nt), u.size());
            fflush(stdout);
        }

        long idum = -1;
        int nzero = 0;
        for(int i=(getNumberOfParticles()-1); i>=0; i--) {
            double eps = rand() % 100; eps /= 100;
            double ksi = gaussian_deviate (& idum );
            // cout << "ksi = " << ksi << endl;
            l = sqrt(2.*D*dt)*ksi*stddev;
            left_right(eps, i, l);
            if(u[i]->getPos() <= tolerance && u[i]->getPos() >= -tolerance) { nzero++; }
        }


        // Erase the elements that were moved outside the interval in this time step
        int k_end = erase_indices.size(); // signed-unsigned trouble in loop
        for(int k=0; k<k_end; k++) {
            int indexToBeRemoved = erase_indices[k];
            swap(u[indexToBeRemoved], u.back());
            u.pop_back();
        }
        erase_indices.clear();

        // u[i]->getPos() <= tolerance && u[i]->getPos() >= -tolerance
        for(int i=(getNumberOfParticles()-1); i>=0; i--) {
            if(u[i]->getPos() == 0.) { nzero++; }
        }
        cout << "number of particles at x = 0: N = " << nzero << endl;

        //Rese number of particles at 0 to N
        for(int k=0; k<N; k++){
            particles *part = new particles(0.);
            AddParticle(part);
            counter2++;
        }

    }

    // If-test counters
    cout << "\nParticles erased " << counter1 << " times" << endl;
    cout << "Particles added " << counter2 << " times" << endl;
    cout << "Particles moved " << counter3 << " times" << endl;


    // Write vector to file:
    // writeToFile("constStepLength", u);
}


void jump::left_right(double eps, int i, double step) {
    double xold = u[i]->getPos();

    if(eps <= 0.5) { // LEFT
        double xnew = xold - step;

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
        double xnew = xold + step;

        if(xnew >= d - tolerance) {
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
        else { cout << "Box " << i << " is empty" << endl;}
    }
}

void jump::writeToFile(string filename, vector<particles*> data){
    string FileName = "../Project5/Data/Histogram_"+filename+".dat";
    cout << FileName << endl;
    ofstream outFile;


    outFile.open(FileName.c_str(), ios::out);


    for (int i = 0; i < getNumberOfParticles(); i ++) {
        outFile << data[i]->getPos() << endl;
    }


    outFile.close();
}

int jump::getNumberOfParticles(){ return u.size();}
