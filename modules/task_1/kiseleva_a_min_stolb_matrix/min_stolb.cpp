// Copyright 2020 Kiseleva Anastasia
#include "../../../modules/task_1/kiseleva_a_min_stolb_matrix/min_stolb.h"
#include <mpi.h>
#include <vector>

std::vector<std::vector<int>> RandomMatrix(int str, int stlb) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<std::vector<int>> matrix(str*stlb);
    std::vector<int> stolb(str);
    for (int i = 0; i < stlb; i++) {
        stolb.clear();
        for (int j = 0; j < str; j++) {
            stolb.push_back(gen() % 10);
        }
        matrix[i] = stolb;
    }
    return matrix;
}

std::vector<int> VVconvertV(std::vector<std::vector<int>> matrix, int str, int stlb) {
    std::vector<int> linm(str * stlb);
    for (int i = 0; i < str; i++) {
        for (int j = 0; j < stlb; j++) {
            linm[i * stlb + j] = matrix[i][j];
        }
    }
    return linm;
}

std::vector<int> Min(std::vector<int> linm, int str, int stlb) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int min = INT_MAX;
    std::vector<int> res(stlb);
    int delta = stlb / size;
    if (stlb % size != 0) {
        delta++;
    }
    MPI_Bcast(linm.data(), str * stlb, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = delta * rank; i < delta * (rank + 1); i++) {
        min = linm[i];
        for (int j = 0; j < str; j++) {
        if (linm[i + j * stlb] <= min) {
                min = linm[i + j * stlb];
            }
        }
        if (rank == 0) {
            res[i] = min;
        } else {
            MPI_Send(&min, 1, MPI_INT, 0, 15, MPI_COMM_WORLD);
        }
    }
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            for (int j = 0; j < delta; j++) {
                MPI_Status status;
                MPI_Recv(&min, 1, MPI_INT, i, 15, MPI_COMM_WORLD, &status);
                res[i * delta + j] = min;
            }
        }
    }
    return res;
}
