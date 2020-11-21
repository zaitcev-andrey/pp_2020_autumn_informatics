// Copyright 2020 Zaitsev Andrey
#include <mpi.h>
#include <vector>
#include <random>
#include <ctime>
#include "../../../modules/task_2/zaitsev_a_hor_and_ver_scheme/hor_and_ver_scheme.h"

std::vector<int> createRandomMatrix(int rows, int cols, time_t seed) {
  std::mt19937 gen(seed);
  std::vector<int> result(rows * cols);
  for (int& i : result)
    i = gen() % 5;
  return result;
}

int scalar_product_of_vectors(const std::vector<int>& vec1, const std::vector<int>& vec2) {
  int result = 0;

  for (int i = 0; i < static_cast<int>(vec1.size()); i++)
    result += vec1[i] * vec2[i];
  return result;
}

std::vector<int> matrix_product(const std::vector<int>& matrix_A, const std::vector<int>& matrix_B,
  int rows_A, int cols_A, int rows_B, int cols_B) {
  std::vector<int> matrix_C(rows_A * cols_B);
  for (int i = 0; i < rows_A; i++) {
    std::vector<int> row_A(matrix_A.begin() + i * cols_A, matrix_A.begin() + i * cols_A + cols_A);
    for (int j = 0; j < cols_B; j++) {
      std::vector<int> col_B(rows_B);
      for (int l = 0; l < rows_B; l++) {
        col_B[l] = matrix_B[l * cols_B + j];
      }
      matrix_C[i * cols_B + j] = scalar_product_of_vectors(row_A, col_B);
    }
  }
  return matrix_C;
}

std::vector<int> matrix_product_parallel(const std::vector<int>& matrix_A, const std::vector<int>& matrix_B,
  int rows_A, int cols_A, int rows_B, int cols_B) {
  int process_size, process_rank;
  MPI_Comm_size(MPI_COMM_WORLD, &process_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

  int stripes = rows_A / process_size;
  int remain = rows_A - stripes * process_size;

  std::vector<int> stripeSize(process_size);
  std::vector<int> displs(process_size);
  if (stripes == 0) {
    for (int i = 0; i < rows_A; i++) {
      stripeSize[i] = cols_B;
      displs[i] = i * cols_B;
    }
  } else {
    int tmp = 0;
    for (int i = 0; i < process_size; i++) {
      if (tmp != remain && remain != 0) {
        tmp++;
        stripeSize[i] = (stripes + 1) * cols_B;
        displs[i] = i * (stripes + 1) * cols_B;
      } else {
        stripeSize[i] = stripes * cols_B;
        displs[i] = remain * cols_B + i * stripes * cols_B;
      }
    }
  }

  if (stripes == 0) {
    if (process_rank == 0) {
      for (int i = 1; i < rows_A; i++) {
        MPI_Send(matrix_A.data() + i * cols_A, cols_A, MPI_INT, i, 0, MPI_COMM_WORLD);
      }
    }
  } else {
    if (process_rank == 0) {
      int tmp = 1;
      for (int process_num = 1; process_num < process_size; process_num++) {
        if (tmp != remain && remain != 0) {
          tmp++;
          MPI_Send(matrix_A.data() + process_num * cols_A * (stripes + 1), cols_A * stripes + cols_A,
      MPI_INT, process_num, 0, MPI_COMM_WORLD);
        } else {
          MPI_Send(matrix_A.data() + process_num * cols_A * stripes + cols_A * remain, cols_A * stripes,
      MPI_INT, process_num, 0, MPI_COMM_WORLD);
        }
      }
    }
  }

  std::vector<int> part_of_rows_A;
  if (stripes == 0) {
    part_of_rows_A.resize(cols_A);
    if (process_rank == 0) {
      part_of_rows_A = { matrix_A.begin(), matrix_A.begin() + cols_A };
    } else if (process_rank < rows_A) {
      MPI_Status status;
      MPI_Recv(&part_of_rows_A[0], cols_A, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }
  } else {
    if (process_rank == 0 && remain != 0) {
      part_of_rows_A.resize(stripes * cols_A + cols_A);
      part_of_rows_A = { matrix_A.begin(), matrix_A.begin() + stripes * cols_A + cols_A };
    } else if (process_rank == 0 && remain == 0) {
      part_of_rows_A.resize(stripes * cols_A);
      part_of_rows_A = { matrix_A.begin(), matrix_A.begin() + stripes * cols_A };
    } else {
      if (1 <= process_rank && process_rank < remain) {
        part_of_rows_A.resize(stripes * cols_A + cols_A);
        MPI_Status status;
        MPI_Recv(&part_of_rows_A[0], (stripes + 1) * cols_A, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
      } else {
        part_of_rows_A.resize(stripes * cols_A);
        MPI_Status status;
        MPI_Recv(&part_of_rows_A[0], stripes * cols_A, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
      }
    }
  }

  std::vector<int> matrix_C;

  if (process_rank == 0) {
    matrix_C.resize(rows_A * cols_B);
  }

  if (process_rank < rows_A) {
    int rows_in_process = part_of_rows_A.size() / cols_A;
    std::vector<int> part_of_matrix_C(rows_in_process * cols_B);


    for (int i = 0; i < rows_in_process; i++) {
      std::vector<int> one_row_A(part_of_rows_A.begin() + i * cols_A, part_of_rows_A.begin() + i * cols_A + cols_A);
      for (int j = 0; j < cols_B; j++) {
        std::vector<int> col_B(rows_B);
        for (int l = 0; l < rows_B; l++) {
          col_B[l] = matrix_B[l * cols_B + j];
        }
        part_of_matrix_C[i * cols_B + j] = scalar_product_of_vectors(one_row_A, col_B);
      }
    }

    MPI_Gatherv(part_of_matrix_C.data(), rows_in_process * cols_B, MPI_INT, matrix_C.data(),
      stripeSize.data(), displs.data(), MPI_INT, 0, MPI_COMM_WORLD);
  }

  return matrix_C;
}
