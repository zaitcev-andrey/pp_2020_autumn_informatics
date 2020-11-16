// Copyright 2020 Kuznetsov Nikita
#include <mpi.h>
#include <vector>
#include <ctime>
#include <random>
#include "../../../modules/task_2/kuznetsov_gaussian_vertical/gaussian_vertical.h"

std::vector<double> getMatrix(int x, int y) {
  std::mt19937 rand_matrix;
  if (x <= 0 || y <= 0)
    throw - 1;
  std::vector<double> mat(x * y);
  rand_matrix.seed(static_cast<unsigned int>(time(0)));
  std::uniform_real_distribution<double> gen(-20, 20);
  for (int i = 0; i < x * y; i++)
    mat[i] = gen(rand_matrix);
  return mat;
}
