// Copyright 2020 Gruzdeva Diana
#ifndef MODULES_TASK_2_GRUZDEVA_D_MAT_MULT_HORIZ_ONLY_MAT_MULT_HORIZ_ONLY_H_
#define MODULES_TASK_2_GRUZDEVA_D_MAT_MULT_HORIZ_ONLY_MAT_MULT_HORIZ_ONLY_H_

#include <mpi.h>
#include <random>
#include <ctime>
#include <vector>

std::vector<int> getRandomMatrix(int rows, int cols, time_t seed);
std::vector<int> getSequentialMultiplication(std::vector<int> matrixA, std::vector<int> matrixB, int aRows);
std::vector<int> getParallelMultiplication(std::vector<int> matrixA, std::vector<int> matrixB, int aRows);

#endif  // MODULES_TASK_2_GRUZDEVA_D_MAT_MULT_HORIZ_ONLY_MAT_MULT_HORIZ_ONLY_H_
