// Copyright 2020 Zaitsev Andrey
#include <mpi.h>
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./hor_and_ver_scheme.h"

TEST(Parallel_matrix_product, MATRICES_100x23_AND_23x70) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

  std::vector<int> matrix_A;
  std::vector<int> matrix_B;
  int rows_A = 100, cols_A = 23, rows_B = 23, cols_B = 70;

  matrix_A = createRandomVector(rows_A, cols_A, time(0));
  matrix_B = createRandomVector(rows_B, cols_B, time(0) + 1);

  std::vector<int> parallel_result = matrix_product_parallel(matrix_A, matrix_B, rows_A, cols_A, rows_B, cols_B);

  if (process_rank == 0) {
    std::vector<int> real_result = matrix_product(matrix_A, matrix_B, rows_A, cols_A, rows_B, cols_B);
    ASSERT_EQ(parallel_result, real_result);
  }
}

TEST(Parallel_matrix_product, MATRICES_40x32_AND_32x45) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

  std::vector<int> matrix_A;
  std::vector<int> matrix_B;
  int rows_A = 40, cols_A = 32, rows_B = 32, cols_B = 45;

  matrix_A = createRandomVector(rows_A, cols_A, time(0));
  matrix_B = createRandomVector(rows_B, cols_B, time(0) + 1);

  std::vector<int> parallel_result = matrix_product_parallel(matrix_A, matrix_B, rows_A, cols_A, rows_B, cols_B);

  if (process_rank == 0) {
    std::vector<int> real_result = matrix_product(matrix_A, matrix_B, rows_A, cols_A, rows_B, cols_B);
    ASSERT_EQ(parallel_result, real_result);
  }
}

TEST(Parallel_matrix_product, MATRICES_25x17_AND_17x14) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

  std::vector<int> matrix_A;
  std::vector<int> matrix_B;
  int rows_A = 25, cols_A = 17, rows_B = 17, cols_B = 14;

  matrix_A = createRandomVector(rows_A, cols_A, time(0));
  matrix_B = createRandomVector(rows_B, cols_B, time(0) + 1);

  std::vector<int> parallel_result = matrix_product_parallel(matrix_A, matrix_B, rows_A, cols_A, rows_B, cols_B);

  if (process_rank == 0) {
    std::vector<int> real_result = matrix_product(matrix_A, matrix_B, rows_A, cols_A, rows_B, cols_B);
    ASSERT_EQ(parallel_result, real_result);
  }
}

TEST(Parallel_matrix_product, MATRICES_15x8_AND_8x12) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

  std::vector<int> matrix_A;
  std::vector<int> matrix_B;
  int rows_A = 15, cols_A = 8, rows_B = 8, cols_B = 12;

  matrix_A = createRandomVector(rows_A, cols_A, time(0));
  matrix_B = createRandomVector(rows_B, cols_B, time(0) + 1);

  std::vector<int> parallel_result = matrix_product_parallel(matrix_A, matrix_B, rows_A, cols_A, rows_B, cols_B);

  if (process_rank == 0) {
    std::vector<int> real_result = matrix_product(matrix_A, matrix_B, rows_A, cols_A, rows_B, cols_B);
    ASSERT_EQ(parallel_result, real_result);
  }
}

TEST(Parallel_matrix_product, MATRICES_7x3_AND_3x2) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

  std::vector<int> matrix_A;
  std::vector<int> matrix_B;
  int rows_A = 7, cols_A = 3, rows_B = 3, cols_B = 2;

  matrix_A = createRandomVector(rows_A, cols_A, time(0));
  matrix_B = createRandomVector(rows_B, cols_B, time(0) + 1);

  std::vector<int> parallel_result = matrix_product_parallel(matrix_A, matrix_B, rows_A, cols_A, rows_B, cols_B);

  if (process_rank == 0) {
    std::vector<int> real_result = matrix_product(matrix_A, matrix_B, rows_A, cols_A, rows_B, cols_B);
    ASSERT_EQ(parallel_result, real_result);
  }
}

TEST(Parallel_matrix_product, MATRICES_7x5_AND_5x2) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

  std::vector<int> matrix_A;
  std::vector<int> matrix_B;
  int rows_A = 7, cols_A = 5, rows_B = 5, cols_B = 2;

  matrix_A = createRandomVector(rows_A, cols_A, time(0));
  matrix_B = createRandomVector(rows_B, cols_B, time(0) + 1);

  std::vector<int> parallel_result = matrix_product_parallel(matrix_A, matrix_B, rows_A, cols_A, rows_B, cols_B);

  if (process_rank == 0) {
    std::vector<int> real_result = matrix_product(matrix_A, matrix_B, rows_A, cols_A, rows_B, cols_B);
    ASSERT_EQ(parallel_result, real_result);
  }
}

TEST(Parallel_matrix_product, MATRICES_3x3_AND_3x3) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

  std::vector<int> matrix_A;
  std::vector<int> matrix_B;
  int rows_A = 3, cols_A = 3, rows_B = 3, cols_B = 3;

  matrix_A = createRandomVector(rows_A, cols_A, time(0));
  matrix_B = createRandomVector(rows_B, cols_B, time(0) + 1);

  std::vector<int> parallel_result = matrix_product_parallel(matrix_A, matrix_B, rows_A, cols_A, rows_B, cols_B);

  if (process_rank == 0) {
    std::vector<int> real_result = matrix_product(matrix_A, matrix_B, rows_A, cols_A, rows_B, cols_B);
    ASSERT_EQ(parallel_result, real_result);
  }
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  MPI_Init(&argc, &argv);

  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners &listeners = ::testing::UnitTest::GetInstance()->listeners();

  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());

  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}
