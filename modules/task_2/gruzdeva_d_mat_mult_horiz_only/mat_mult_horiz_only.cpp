// Copyright 2020 Gruzdeva Diana

#include "../../../modules/task_2/gruzdeva_d_mat_mult_horiz_only/mat_mult_horiz_only.h"
#include <random>
#include <vector>
#include <ctime>
#include <iostream>

std::vector<int> getRandomMatrix(int rows, int cols, time_t seed) {
    std::vector<int> mat(rows * cols);
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dis(-10, 10);
    for (int i = 0; i < rows * cols; i++) {
        mat[i] = dis(gen);
    }
    return mat;
}


std::vector<int> getSequentialMultiplication(std::vector<int> matrixA, std::vector<int> matrixB, int aRows) {
    std::vector<int> matrixC(matrixA.size());
    for (int i = 0; i < matrixA.size() / aRows; i++) {
        for (int j = 0; j < aRows; j++) {
            matrixC[i * aRows + j] = 0;
            for (int k = 0; k < aRows; k++) {
                matrixC[i * aRows + j] += matrixA[i * aRows + k] * matrixB[j + k * aRows];
            }
        }
    }
    return matrixC;
}

std::vector<int> getParallelMultiplication(std::vector<int> matrixA, std::vector<int> matrixB, int aRows) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int stripeHeight = aRows / size;
    std::vector<int> matrixC(aRows * aRows);

    std::vector<int> matrixAStripe(stripeHeight * aRows);
    std::vector<int> matrixBStripe(aRows * aRows);
    std::vector<int> matrixCStripe;
    MPI_Status status;

    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            MPI_Send(&matrixA[0] + i * stripeHeight * aRows, stripeHeight * aRows, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&matrixB[0], aRows * aRows, MPI_INT, i, 1, MPI_COMM_WORLD);
        }
    }

    if (rank == 0) {
        matrixAStripe = std::vector<int>(matrixA.begin(), matrixA.begin() + stripeHeight * aRows);
        matrixBStripe = std::vector<int>(matrixB.begin(), matrixB.begin() + aRows * aRows);
    } else {
        MPI_Recv(&matrixAStripe[0], stripeHeight * aRows, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&matrixBStripe[0], stripeHeight * stripeHeight * aRows  * aRows,
                 MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
    }

    matrixCStripe = getSequentialMultiplication(matrixAStripe, matrixBStripe, aRows);
    MPI_Allgather(matrixCStripe.data(), stripeHeight * aRows,
                  MPI_INT, matrixC.data(), stripeHeight * aRows, MPI_INT, MPI_COMM_WORLD);

    if (rank == 0) {
        matrixAStripe = std::vector<int>(matrixA.begin() + size * stripeHeight * aRows, matrixA.end());
        std::vector<int> remaining = getSequentialMultiplication(matrixAStripe, matrixBStripe, aRows);
        for (unsigned int i = 0; i < remaining.size(); i++) {
            matrixC[size * stripeHeight * aRows + i] = remaining[i];
        }
    }

    return matrixC;
}
