// Copyright 2020 Zaitsev Andrey
#ifndef MODULES_TASK_3_ZAITSEV_A_VERT_GAUSS_VERT_GAUSS_H_
#define MODULES_TASK_3_ZAITSEV_A_VERT_GAUSS_VERT_GAUSS_H_

#include <vector>
#include <random>
#include <ctime>

int clamp(int value, int max, int min);
std::vector<double> createRandomMatrix(int rows, int cols);
std::vector<double> transposition(const std::vector<double>& matrix, int rows, int cols);
std::vector<double> createGaussianKernel(int radius, int sigma);
std::vector<double> gauss_filter_sequence(const std::vector<double>& matrix, int rows, int cols, int radius, int sigma);
std::vector<double> gauss_filter_part_parallel(const std::vector<double>& matrix, int rows, int cols, int count_cols,
  const std::vector<int>& coord_x, const std::vector<double>& kernel, int radius, int sigma);
std::vector<double> gauss_filter_parallel(const std::vector<double>& matrix, int rows, int cols, int radius, int sigma);

#endif  // MODULES_TASK_3_ZAITSEV_A_VERT_GAUSS_VERT_GAUSS_H_
