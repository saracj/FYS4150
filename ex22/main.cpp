#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    int j, len; // Declaring integer variables
    // float sup, sdown; // Declaring floating variables
    // double Sup, Sdown, rel_diff, Rel_Diff; // Declaring floating variables with double precission

    // cout << "Enter N: ";
    // cin >> N; //Reads in N

    cout << "hi" << endl;

    long int i, N[4] = {1000, 100000, 100000000, 10000000000};
    len = sizeof(N)/sizeof(*N);
    float sup[len], sdown[len];
    double Sup[len], Sdown[len], rel_diff[len], Rel_Diff[len];

    for(i=0; i<len; i++){
        sup[i] = 0;
        sdown[i] = 0;
        Sup[i] = 0;
        Sdown[i] = 0;

        for (j=1; j<N[i]; j++){
            sup[i] += 1./j;
            Sup[i] += 1./j;
        }

        for (j=N[i]; j>0; j--){
            sdown[i] += 1./j;
            Sdown[i] += 1./j;
        }

        // Computing relative error:
        rel_diff[i] = (sup[i] - sdown[i])/sdown[i];
        Rel_Diff[i] = (Sup[i] - Sdown[i])/Sdown[i];
        printf("\nRelative error with double precission: Rel(N=%i) = %g", N[i], Rel_Diff[i]);
        printf("\nRelative error with single precission: rel(N=%i) = %g", N[i], rel_diff[i]);
        printf("\n------------------------------------------------------------------\n");
    }
    /*
    cout << "s_up = " << sup << endl;
    cout << "s_down = " << sdown << endl;
    cout << "S_up (double) = " << Sup << endl;
    cout << "S_down (double) = " << Sdown << endl;
    cout << "Relative error with single precission: R = " << rel_diff << endl;
    cout << "Relative error with double precission: R = " << Rel_Diff << endl;
    */

    return 0;
}
