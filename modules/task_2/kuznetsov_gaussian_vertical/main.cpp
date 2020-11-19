// Copyright 2020 Kuznetsov Nikita
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./gaussian_vertical.h"

TEST(GAUSSIAN_STRIP_VERTICAL_SCHEME, THROWS_WHEN_GENERATE_MATRIX_SIZE_LOWER_THAN_ZERO) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    std::vector<double> mat;
    const int size = -10;
    ASSERT_ANY_THROW(mat = getMatrix(size));
  }
}

TEST(GAUSSIAN_STRIP_VERTICAL_SCHEME, SUCCESSFULLY_GENERATED_MATRIX) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    std::vector<double> mat;
    const int size = 3;
    ASSERT_NO_THROW(mat = getMatrix(size));
  }
}

TEST(GAUSSIAN_STRIP_VERTICAL_SCHEME, VERIFY_SEQUENTIAL_METHOD) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    const int size = 3;
    std::vector<double> mat = { 1, 2, 3, 1, 2, -1, 2, 6, 1, 1, 5, -1 };
    std::vector<double> res = { 4, 0, -1 };
    std::vector<double> res_ = sequentialMethod(mat, size);
    ASSERT_EQ(res_, res);
  }
}

TEST(GAUSSIAN_STRIP_VERTICAL_SCHEME, VERIFY_PARALLEL_METHOD) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    const int size = 3;
    std::vector<double> mat = { 4, 2, -1, 1, 5, 3, -2, 2, 3, 2, -3, 0 };
    std::vector<double> res = { -1, 3, 1 };
    ASSERT_EQ(parallelMethod(mat, size), res);
  }
}

TEST(GAUSSIAN_STRIP_VERTICAL_SCHEME, SEQUENTIAL_EQUAL_PARALLEL_METHOD) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    const int size = 3;
    std::vector<double> mat = { 4, 2, -1, 1, 5, 3, -2, 2, 3, 2, -3, 0 };
    ASSERT_EQ(sequentialMethod(mat, size), parallelMethod(mat, size));
  }
}

TEST(GAUSSIAN_STRIP_VERTICAL_SCHEME, THROWS_WHEN_SIZE_IS_LOWER_THAN_ZERO_SEQ) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    const int size = -10;
    std::vector<double> mat = { 4, 2, -1, 1, 5, 3, -2, 2, 3, 2, -3, 0 };
    ASSERT_ANY_THROW(sequentialMethod(mat, size));
  }
}

TEST(GAUSSIAN_STRIP_VERTICAL_SCHEME, THROWS_WHEN_SIZE_IS_LOWER_THAN_ZERO_PAR) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    const int size = -10;
    std::vector<double> mat = { 4, 2, -1, 1, 5, 3, -2, 2, 3, 2, -3, 0 };
    ASSERT_ANY_THROW(parallelMethod(mat, size));
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  MPI_Init(&argc, &argv);

  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());

  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}
