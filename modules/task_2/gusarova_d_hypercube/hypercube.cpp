// Copyright 2020 Gysarova Daria
#include <mpi.h>
#include<algorithm>
#include "../../../modules/task_2/gusarova_d_hypercube/hypercube.h"

int Dim(int size) {
    int newsize = 1;
    int d = 0;
    while (size >= newsize * 2) {
        newsize *= 2;
        d++;
    }
    return d;
}
MPI_Comm HyperCube() {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int k = Dim(size);
    int* dims;
    int* periods;
    dims = new int[k];
    periods = new int[k];
    for (int i = 0; i < k; i++) {
        dims[i] = 2;
        periods[i] = 1;
    }
    MPI_Comm newcomm;
    MPI_Cart_create(MPI_COMM_WORLD, k, dims, periods, 0, &newcomm);
    delete[] dims;
    delete[] periods;
    return newcomm;
}
