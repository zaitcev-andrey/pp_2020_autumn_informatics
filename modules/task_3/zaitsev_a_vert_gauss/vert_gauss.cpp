// Copyright 2020 Zaitsev Andrey
#include <mpi.h>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include "../../../modules/task_3/zaitsev_a_vert_gauss/vert_gauss.h"

int clamp(int value, int max, int min) {
  value = value > max ? max : value;
  return value < min ? min : value;
}

std::vector<double> createRandomMatrix(int rows, int cols) {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  std::vector<double> result(rows * cols);
  for (int i = 0; i < rows * cols; i++)
    result[i] = gen() % 256;
  return result;
}

std::vector<double> transposition(const std::vector<double>& matrix, int rows, int cols) {
  std::vector<double> result(rows * cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      result[i + j * rows] = matrix[i * cols + j];
    }
  }
  return result;
}

std::vector<double> createGaussianKernel(int radius, int sigma) {
  int diametr = 2 * radius + 1;
  // coef of normalization of kernel
  double norm = 0;
  // creating gauss kernel
  std::vector<double> kernel(diametr * diametr);

  // calculating filter kernel
  for (int i = -radius; i <= radius; i++) {
    for (int j = -radius; j <= radius; j++) {
      int idx = (i + radius) * diametr + j + radius;
      kernel[idx] = exp(-(i * i + j * j) / (sigma * sigma));
      norm += kernel[idx];
    }
  }

  // normalizing the kernel
  for (int i = 0; i < diametr * diametr; i++)
    kernel[i] /= norm;
  return kernel;
}

std::vector<double> gauss_filter_sequence(const std::vector<double>& matrix, int rows, int cols,
  int radius, int sigma) {
  std::vector<double> result(rows * cols);
  const unsigned int diametr = 2 * radius + 1;
  std::vector<double> kernel = createGaussianKernel(radius, sigma);
  for (int x = 0; x < rows; x++) {
    for (int y = 0; y < cols; y++) {
      double res = 0;
      for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
          int idx = (i + radius) * diametr + j + radius;

          int x_ = clamp(x + j, rows - 1, 0);
          int y_ = clamp(y + i, cols - 1, 0);

          double value = matrix[x_ * cols + y_];

          res += value * kernel[idx];
        }
      }
      res = clamp(res, 255, 0);
      result[x * cols + y] = res;
    }
  }
  return result;
}

std::vector<double> gauss_filter_part_parallel(const std::vector<double>& matrix, int rows, int cols, int count_rows,
  const std::vector<int>& coord_x, const std::vector<double>& kernel, int radius, int sigma) {
  std::vector<double> result(count_rows * cols);
  const unsigned int diametr = 2 * radius + 1;
  for (int x = 0; x < count_rows; x++) {
    for (int y = 0; y < cols; y++) {
      double res = 0;
      for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
          int idx = (i + radius) * diametr + j + radius;

          int x_ = clamp(coord_x[x] + j, rows - 1, 0);
          int y_ = clamp(y + i, cols - 1, 0);

          double value = matrix[x_ * cols + y_];

          res += value * kernel[idx];
        }
      }
      res = clamp(res, 255, 0);
      result[x * cols + y] = res;
    }
  }
  return result;
}

std::vector<double> gauss_filter_parallel(const std::vector<double>& matrix, int rows, int cols,
  int radius, int sigma) {
  int process_size, process_rank;
  MPI_Comm_size(MPI_COMM_WORLD, &process_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

  int stripes = rows / process_size;
  int part_elem_number = stripes * cols;
  std::vector<double> matrix_local(part_elem_number);

  MPI_Scatter(matrix.data(), part_elem_number, MPI_DOUBLE, matrix_local.data(),
    part_elem_number, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  std::vector<int> coord_x;
  for (int i = 0; i < stripes; i++)
    coord_x.push_back(stripes * process_rank + i);

  std::vector<double> kernel = createGaussianKernel(radius, sigma);

  std::vector<double> local_result = gauss_filter_part_parallel(matrix, rows, cols,
    stripes, coord_x, kernel, radius, sigma);
  std::vector<double> global_result(rows * cols);

  MPI_Gather(local_result.data(), part_elem_number, MPI_DOUBLE, global_result.data(),
    part_elem_number, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  if (process_rank == 0) {
    int remain = rows % process_size;
    if (remain != 0) {
      std::vector<int> tmp;
      for (int i = stripes * process_size; i < rows; i++)
        tmp.push_back(i);
      local_result = gauss_filter_part_parallel(matrix, rows, cols, remain, tmp, kernel, radius, sigma);

      for (int i = 0; i < static_cast<int>(local_result.size()); i++)
        global_result[stripes * process_size * cols + i] = local_result[i];
    }
  }

  return global_result;
}
