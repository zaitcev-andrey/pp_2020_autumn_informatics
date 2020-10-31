// Copyright 2020 Zaikin Ilya
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <ctime>
#include "./montecarlo.h"
using namespace std;
float MonteCarloNotParallelMethod(double b, double a, int n, double(*func)(double)) {
	float x;
	float y = 0;
	float integral;
	float koef = (float)b - a;
	float te;
	srand(time(0));
	if (n == 0) {
		throw - 1;
	}
	else {
		for (int i = 0; i < n; i++) {
			te = ((float)rand() / RAND_MAX);
			x = a + te * (b - a);
			y += func(x);
		}
		integral = ((float)1 / n) * koef * (float)y;
		return integral;
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
	float integral;
	float koef = (float)b - a;
	float te;
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	startwtime = MPI_Wtime();
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	if (n == 0) {
		throw - 1;
	}
	else {
		y = 0.0;
		srand(time(0));
		for (int i = myid + 1; i <= n; i += numprocs) {

			te = ((float)rand() / RAND_MAX);
			x = a + te * (b - a);
			y += func(x);
		}
		integral = ((float)1 / n) * koef * (float)y;
		MPI_Reduce(&integral, &res, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
		if (myid == 0) {
		endwtime = MPI_Wtime();
		cout << endwtime - startwtime << endl;
		}
	}
	return res;
}
