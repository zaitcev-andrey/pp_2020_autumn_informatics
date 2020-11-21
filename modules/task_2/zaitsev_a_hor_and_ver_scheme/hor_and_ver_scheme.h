// Copyright 2020 Zaitsev Andrey
#ifndef MODULES_TASK_2_ZAITSEV_A_HOR_AND_VER_SCHEME_HOR_AND_VER_SCHEME_H_
#define MODULES_TASK_2_ZAITSEV_A_HOR_AND_VER_SCHEME_HOR_AND_VER_SCHEME_H_

#include <vector>
#include <random>
#include <ctime>

std::vector<int> createRandomMatrix(int rows, int cols, time_t seed);
int scalar_product_of_vectors(const std::vector<int>& vec1, const std::vector<int>& vec2);
std::vector<int> matrix_product(const std::vector<int>& matrix_A, const std::vector<int>& matrix_B,
  int rows_A, int cols_A, int rows_B, int cols_B);
std::vector<int> matrix_product_parallel(const std::vector<int>& matrix_A, const std::vector<int>& matrix_B,
  int rows_A, int cols_A, int rows_B, int cols_B);

#endif  // MODULES_TASK_2_ZAITSEV_A_HOR_AND_VER_SCHEME_HOR_AND_VER_SCHEME_H_
