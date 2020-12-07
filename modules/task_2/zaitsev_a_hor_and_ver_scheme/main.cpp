// Copyright 2020 Zaitsev Andrey
#include <mpi.h>
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./hor_and_ver_scheme.h"

TEST(Parallel_matrix_product, 17x17) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
  int size = 17;
  std::vector<double> matrix_A;
  std::vector<double> matrix_B;
  if (process_rank == 0) {
    matrix_A = createRandomMatrix(size, time(0));
    matrix_B = createRandomMatrix(size, time(0));
    matrix_B = transposition(matrix_B, size);
  }
  double start1 = MPI_Wtime();
  std::vector<double> parallel_result = matrix_product_parallel(matrix_A, matrix_B, size);
  double finish1 = MPI_Wtime();
  if (process_rank == 0) {
	double start2 = MPI_Wtime();
    std::vector<double> real_result = matrix_product_sequential(matrix_A, matrix_B, size);
	double finish2 = MPI_Wtime();
    ASSERT_EQ(parallel_result, real_result);
	std::cout << finish1 - start1 << std::endl;
	std::cout << finish2 - start2 << std::endl;
  }
}

TEST(Parallel_matrix_product, 35x35) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
  int size = 35;
  std::vector<double> matrix_A;
  std::vector<double> matrix_B;
  if (process_rank == 0) {
    matrix_A = createRandomMatrix(size, time(0));
    matrix_B = createRandomMatrix(size, time(0));
    matrix_B = transposition(matrix_B, size);
  }
  double start1 = MPI_Wtime();
  std::vector<double> parallel_result = matrix_product_parallel(matrix_A, matrix_B, size);
  double finish1 = MPI_Wtime();
  if (process_rank == 0) {
	  double start2 = MPI_Wtime();
	  std::vector<double> real_result = matrix_product_sequential(matrix_A, matrix_B, size);
	  double finish2 = MPI_Wtime();
	  ASSERT_EQ(parallel_result, real_result);
	  std::cout << finish1 - start1 << std::endl;
	  std::cout << finish2 - start2 << std::endl;
  }
}
TEST(Parallel_matrix_product, 16x16) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
  int size = 16;
  std::vector<double> matrix_A;
  std::vector<double> matrix_B;
  if (process_rank == 0) {
    matrix_A = createRandomMatrix(size, time(0));
    matrix_B = createRandomMatrix(size, time(0));
    matrix_B = transposition(matrix_B, size);
  }
  double start1 = MPI_Wtime();
  std::vector<double> parallel_result = matrix_product_parallel(matrix_A, matrix_B, size);
  double finish1 = MPI_Wtime();
  if (process_rank == 0) {
	  double start2 = MPI_Wtime();
	  std::vector<double> real_result = matrix_product_sequential(matrix_A, matrix_B, size);
	  double finish2 = MPI_Wtime();
	  ASSERT_EQ(parallel_result, real_result);
	  std::cout << finish1 - start1 << std::endl;
	  std::cout << finish2 - start2 << std::endl;
  }
}
TEST(Parallel_matrix_product, 6x6) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
  int size = 6;
  std::vector<double> matrix_A;
  std::vector<double> matrix_B;
  if (process_rank == 0) {
    matrix_A = createRandomMatrix(size, time(0));
    matrix_B = createRandomMatrix(size, time(0));
    matrix_B = transposition(matrix_B, size);
  }
  double start1 = MPI_Wtime();
  std::vector<double> parallel_result = matrix_product_parallel(matrix_A, matrix_B, size);
  double finish1 = MPI_Wtime();
  if (process_rank == 0) {
	  double start2 = MPI_Wtime();
	  std::vector<double> real_result = matrix_product_sequential(matrix_A, matrix_B, size);
	  double finish2 = MPI_Wtime();
	  ASSERT_EQ(parallel_result, real_result);
	  std::cout << finish1 - start1 << std::endl;
	  std::cout << finish2 - start2 << std::endl;
  }
}
TEST(Parallel_matrix_product, 10x10) {
  int process_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
  int size = 10;
  std::vector<double> matrix_A;
  std::vector<double> matrix_B;
  if (process_rank == 0) {
    matrix_A = createRandomMatrix(size, time(0));
    matrix_B = createRandomMatrix(size, time(0));
    matrix_B = transposition(matrix_B, size);
  }
  double start1 = MPI_Wtime();
  std::vector<double> parallel_result = matrix_product_parallel(matrix_A, matrix_B, size);
  double finish1 = MPI_Wtime();
  if (process_rank == 0) {
	  double start2 = MPI_Wtime();
	  std::vector<double> real_result = matrix_product_sequential(matrix_A, matrix_B, size);
	  double finish2 = MPI_Wtime();
	  ASSERT_EQ(parallel_result, real_result);
	  std::cout << finish1 - start1 << std::endl;
	  std::cout << finish2 - start2 << std::endl;
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
