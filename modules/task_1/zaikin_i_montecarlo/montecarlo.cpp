#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <ctime>
#include "montecarlo.h"
using namespace std;
float MonteCarloNotParallelMethod(double b, double a, int n, double(*func)(double)) {
    float x;
    float y = 0;
    float Integral;
    float koef = static_cast<float>(b) - a;
    float te;
    srand(time(0));
    if (n == 0) {
        throw - 1;
    } else {
        for (int i = 0; i < n; i++) {
            te = (static_cast<float>(rand()) / RAND_MAX);
            x = a + te * (b - a);
            y += func(x);
        }
        Integral = (static_cast<float>(1) / n) * koef * static_cast<float>(y);
        return Integral;
    }
}
float MonteCarloParallelMethod(double b, double a, int n, double(*func)(double)) {
    int myid;
    int numprocs;
    float res;
    double startwtime = 0.0, endwtime;
    int namelen;
    float x;
    float y = 0;
    float Integral;
    float koef = static_cast<float>(b) - a;
    float te;
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    startwtime = MPI_Wtime();
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (n == 0) {
        throw - 1;
    } else {
        y = 0.0;
        srand(time(0));
        for (int i = myid + 1; i <= n; i += numprocs) {
            te = (static_cast<float>(rand()) / RAND_MAX);
            x = a + te * (b - a);
            y += func(x);
        }
        Integral = (static_cast<float>(1) / n) * koef * (static_cast<float>(y));
        MPI_Reduce(&Integral, &res, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
        if (myid == 0) {
            endwtime = MPI_Wtime();
            cout << endwtime - startwtime << endl;
        }
    }   
    return res;
}
