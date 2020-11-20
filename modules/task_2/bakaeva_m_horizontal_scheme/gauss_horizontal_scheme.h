// Copyright 2020 Bakaeva Maria
#ifndef MODULES_TASK_2_BAKAEVA_M_HORIZONTAL_SCHEME_GAUSS_HORIZONTAL_SCHEME_H_
#define MODULES_TASK_2_BAKAEVA_M_HORIZONTAL_SCHEME_GAUSS_HORIZONTAL_SCHEME_H_


//double* generateMatrix(int size);
void getSequentialGauss(const double* matrix, double* result, int size);
void getParallelGauss(const double* matrixGlobal, double* result, int cols, int rows);
#endif  // MODULES_TASK_2_BAKAEVA_M_HORIZONTAL_SCHEME_GAUSS_HORIZONTAL_SCHEME_H_