// Copyright 2020 Gruzdeva Diana
#ifndef MODULES_TASK_2_GRUZDEVA_D_MAT_MULT_HORIZ_STRIPE_A_MAT_MULT_HORIZ_STRIPE_A_H_
#define MODULES_TASK_2_GRUZDEVA_D_MAT_MULT_HORIZ_STRIPE_A_MAT_MULT_HORIZ_STRIPE_A_H_

#include <mpi.h>
#include <random>  
#include <ctime>

int** getRandomMatrix(int width, int height, time_t seed);
int** getSequentialMultiplication(int** matrixA, int** matrixB, int matrixAHeight, int matrixAWidth, int matrixBWidth);
int** getParalleMultiplication(int** matrixA, int** matrixB, int matrixAHeight, int matrixAWidth, int matrixBWidth);

#endif  // MODULES_TASK_2_GRUZDEVA_D_MAT_MULT_HORIZ_STRIPE_A_MAT_MULT_HORIZ_STRIPE_A_H_
