// Copyright 2020 Rustamov Azer
#include <mpi.h>
#include <random>
#include <ctime>
#include <algorithm>
#include "../../../modules/task_1/rustamov_a_matrix_cols_sum/matrix_cols_sum.h"

int* RandomMatrix(int rows, int cols) {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    int matrix[rows][cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = static_cast<int>(mersenne() % 100u);
        }
    }
    return matrix;
}

int* Transpose(int* matrix, int rows, int cols) {
    int transpose[cols][rows];
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
             transpose[j][i] = matrix[i][j];
        }
    }
    return transpose;
}

int* SequentialColsSum(int* transposed_matrix, int rows, int cols) {
    if(rows * cols == 0) {
        throw "Invalid matrix size.";
    }
    int sum[rows];
    std::fill(sum,sum+rows, 0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; i < cols; j++)
        {
            sum[i] += transposed_matrix[i*cols + j];
        }
    }
    return sum;
}

int* ParallelColsSum(int* matrix, int rows, int cols) {
    if (rows * cols == 0) {
        throw "Invalid matrix size";
    }
    int* transposed_matrix = Transpose(matrix, rows, cols);
    int tr_rows = cols;
    int tr_cols = rows;
    int procNum, procRank;
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    const int n = tr_rows / procNum;
    int delta = tr_rows % procNum;
    int local_tr_matrix[n][tr_cols];
    int local_sum[n];
    int zero_sum[n+delta];
    int global_sum[tr_rows]
    if (procRank == 0) {
        for (int i = 1; i < procNum; i++)
            MPI_Send(transposed_matrix + delta + i * n, n, MPI_INT, i, 0, MPI_COMM_WORLD);
        zero_sum = SequentialColsSum(transposed_matrix, n + delta, tr_cols);
        for (int i = 1; i < procNum; i++)
        {
            MPI_Status status;
            MPI_Recv(global_sum[delta + i * n], n, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        }
    } else {
        MPI_Status status;
        MPI_Recv(local_tr_matrix, n * tr_cols, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        local_sum = SequentialColsSum(local_tr_matrix, n, tr_cols);
        MPI_Send(local_sum, n, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    return global_sum;
}
