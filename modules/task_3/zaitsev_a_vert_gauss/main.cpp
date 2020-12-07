// Copyright 2020 Zaitsev Andrey
#include <mpi.h>
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include "./vert_gauss.h"

TEST(Verify_transposition, 2x4) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

  if (process_rank == 0) {
    int rows = 2;
    int cols = 4;
    std::vector<double> matrix(rows * cols);
    matrix[0] = 12;
    matrix[1] = 250;
    matrix[2] = 196;
    matrix[3] = 17;
    matrix[4] = 59;
    matrix[5] = 83;
    matrix[6] = 115;
    matrix[7] = 205;

    std::vector<double> answer(rows * cols);
    answer[0] = 12;
    answer[1] = 59;
    answer[2] = 250;
    answer[3] = 83;
    answer[4] = 196;
    answer[5] = 115;
    answer[6] = 17;
    answer[7] = 205;

    matrix = transposition(matrix, rows, cols);
    int tmp = rows;
    rows = cols;
    cols = tmp;

    ASSERT_EQ(matrix, answer);
  }
}

TEST(Parallel_gauss_filter_random_matrix, 200x165) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
  int rows = 200;
  int cols = 165;
  std::vector<double> matrix = createRandomMatrix(rows, cols);

  matrix = transposition(matrix, rows, cols);
  int tmp = rows;
  rows = cols;
  cols = tmp;

  clock_t start1 = clock();
  std::vector<double> parallel_result = gauss_filter_parallel(matrix, rows, cols, 1, 5);
  clock_t finish1 = clock();
  if (process_rank == 0) {
    clock_t start2 = clock();
    std::vector<double> real_result = gauss_filter_sequence(matrix, rows, cols, 1, 5);
    clock_t finish2 = clock();
    ASSERT_EQ(parallel_result, real_result);
    std::cout << "Parallel: " << finish1 - start1 << std::endl;
    std::cout << "Sequence: " << finish2 - start2 << std::endl;
  }
}

TEST(Parallel_gauss_filter, 3x3) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
  int rows = 3;
  int cols = 3;
  std::vector<double> matrix(rows * cols);

  matrix[0] = 148;
  matrix[1] = 74;
  matrix[2] = 88;
  matrix[3] = 133;
  matrix[4] = 154;
  matrix[5] = 19;
  matrix[6] = 23;
  matrix[7] = 40;
  matrix[8] = 92;

  matrix = transposition(matrix, rows, cols);
  int tmp = rows;
  rows = cols;
  cols = tmp;

  double start1 = MPI_Wtime();
  std::vector<double> parallel_result = gauss_filter_parallel(matrix, rows, cols, 1, 5);
  double finish1 = MPI_Wtime();
  if (process_rank == 0) {
    double start2 = MPI_Wtime();
    std::vector<double> real_result = gauss_filter_sequence(matrix, rows, cols, 1, 5);
    double finish2 = MPI_Wtime();
    ASSERT_EQ(parallel_result, real_result);
    std::cout << "Parallel: " << finish1 - start1 << std::endl;
    std::cout << "Sequence: " << finish2 - start2 << std::endl;
  }
}

TEST(Parallel_gauss_filter, 3x4) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
  int rows = 3;
  int cols = 4;
  std::vector<double> matrix(rows * cols);

  matrix[0] = 120;
  matrix[1] = 43;
  matrix[2] = 84;
  matrix[3] = 18;
  matrix[4] = 53;
  matrix[5] = 99;
  matrix[6] = 207;
  matrix[7] = 0;
  matrix[8] = 254;
  matrix[9] = 98;
  matrix[10] = 102;
  matrix[11] = 44;

  matrix = transposition(matrix, rows, cols);
  int tmp = rows;
  rows = cols;
  cols = tmp;

  double start1 = MPI_Wtime();
  std::vector<double> parallel_result = gauss_filter_parallel(matrix, rows, cols, 1, 5);
  double finish1 = MPI_Wtime();
  if (process_rank == 0) {
    double start2 = MPI_Wtime();
    std::vector<double> real_result = gauss_filter_sequence(matrix, rows, cols, 1, 5);
    double finish2 = MPI_Wtime();
    ASSERT_EQ(parallel_result, real_result);
    std::cout << "Parallel: " << finish1 - start1 << std::endl;
    std::cout << "Sequence: " << finish2 - start2 << std::endl;
  }
}

TEST(Parallel_gauss_filter, 5x3) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
  int rows = 5;
  int cols = 3;
  std::vector<double> matrix(rows * cols);

  matrix[0] = 125;
  matrix[1] = 25;
  matrix[2] = 36;
  matrix[3] = 187;
  matrix[4] = 202;
  matrix[5] = 163;
  matrix[6] = 233;
  matrix[7] = 44;
  matrix[8] = 5;
  matrix[9] = 150;
  matrix[10] = 100;
  matrix[11] = 208;
  matrix[12] = 75;
  matrix[13] = 10;
  matrix[14] = 28;

  matrix = transposition(matrix, rows, cols);
  int tmp = rows;
  rows = cols;
  cols = tmp;

  double start1 = MPI_Wtime();
  std::vector<double> parallel_result = gauss_filter_parallel(matrix, rows, cols, 1, 5);
  double finish1 = MPI_Wtime();
  if (process_rank == 0) {
    double start2 = MPI_Wtime();
    std::vector<double> real_result = gauss_filter_sequence(matrix, rows, cols, 1, 5);
    double finish2 = MPI_Wtime();
    ASSERT_EQ(parallel_result, real_result);
    std::cout << "Parallel: " << finish1 - start1 << std::endl;
    std::cout << "Sequence: " << finish2 - start2 << std::endl;
  }
}

TEST(Parallel_gauss_filter, 7x2) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
  int rows = 7;
  int cols = 2;
  std::vector<double> matrix(rows * cols);

  matrix[0] = 40;
  matrix[1] = 55;
  matrix[2] = 38;
  matrix[3] = 121;
  matrix[4] = 74;
  matrix[5] = 43;
  matrix[6] = 65;
  matrix[7] = 49;
  matrix[8] = 3;
  matrix[9] = 195;
  matrix[10] = 10;
  matrix[11] = 208;
  matrix[12] = 15;
  matrix[13] = 48;

  matrix = transposition(matrix, rows, cols);
  int tmp = rows;
  rows = cols;
  cols = tmp;

  double start1 = MPI_Wtime();
  std::vector<double> parallel_result = gauss_filter_parallel(matrix, rows, cols, 1, 5);
  double finish1 = MPI_Wtime();
  if (process_rank == 0) {
    double start2 = MPI_Wtime();
    std::vector<double> real_result = gauss_filter_sequence(matrix, rows, cols, 1, 5);
    double finish2 = MPI_Wtime();
    ASSERT_EQ(parallel_result, real_result);
    std::cout << "Parallel: " << finish1 - start1 << std::endl;
    std::cout << "Sequence: " << finish2 - start2 << std::endl;
  }
}

TEST(Parallel_gauss_filter, 5x1) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
  int rows = 5;
  int cols = 1;
  std::vector<double> matrix(rows * cols);

  matrix[0] = 16;
  matrix[1] = 38;
  matrix[2] = 253;
  matrix[3] = 88;
  matrix[4] = 144;

  matrix = transposition(matrix, rows, cols);
  int tmp = rows;
  rows = cols;
  cols = tmp;

  double start1 = MPI_Wtime();
  std::vector<double> parallel_result = gauss_filter_parallel(matrix, rows, cols, 1, 5);
  double finish1 = MPI_Wtime();
  if (process_rank == 0) {
    double start2 = MPI_Wtime();
    std::vector<double> real_result = gauss_filter_sequence(matrix, rows, cols, 1, 5);
    double finish2 = MPI_Wtime();
    ASSERT_EQ(parallel_result, real_result);
    std::cout << "Parallel: " << finish1 - start1 << std::endl;
    std::cout << "Sequence: " << finish2 - start2 << std::endl;
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
