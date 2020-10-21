// Copyright 2020 Rustamov Azer
#ifndef MODULES_TASK_1_RUSTAMOV_A_MATRIX_COLS_SUM_MATRIX_COLS_SUM_H_
#define MODULES_TASK_1_RUSTAMOV_A_MATRIX_COLS_SUM_MATRIX_COLS_SUM_H_

int* RandomMatrix(int rows, int cols);
int* Transpose(int* matrix, int rows, int cols);
int* SequentialColsSum(int* transposed_matrix, int rows, int *sum);
int* ParallelColsSum(int* matrix, int rows, int cols);

#endif // MODULES_TASK_1_RUSTAMOV_A_MATRIX_COLS_SUM_MATRIX_COLS_SUM_H_
