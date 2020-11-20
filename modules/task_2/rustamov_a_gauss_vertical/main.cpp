// Copyright 2020 Rustamov Azer
#include <mpi.h>
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./gauss_vertical.h"

TEST(GAUSSIAN_STRIP_VERTICAL_SCHEME, SUCCESSFULL_PARALLEL_METHOD) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  const int size = 3;
  std::vector<double> mat = { 4, 2, -1, 1, 5, 3, -2, 2, 3 };
  std::vector<double> vec = { 2, -3, 0 };
  std::vector<double> result = ParallelGauss(mat, 3, 3, vec, 3);
  if (rank == 0) {
    std::vector<double> exRes = { -1, 3, 1 };
    ASSERT_EQ(result, exRes);
  }
}

TEST(Gauss_Vertical, Incorrect_sizes) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int rows = 0, cols = 10, vecSize = 10;
    Matrix matrix;
    std::vector<double> vec;
    if (procRank == 0) {
        matrix = RandomMatrix(rows, cols);
        vec = RandomMatrix(vecSize, 1);
    }
    ASSERT_ANY_THROW(ParallelGauss(matrix, rows, cols, vec, vecSize));
}
TEST(Gauss_Vertical, 5x5x5) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int rows = 5, cols = 5, vecSize = 5;
    Matrix matrix;
    Matrix vec;
    Matrix res1, res2;
    if (procRank == 0) {
        matrix = RandomMatrix(rows, cols);
        vec = RandomMatrix(vecSize, 1);
    }
    res1 = ParallelGauss(matrix, rows, cols, vec, vecSize);
    if (procRank == 0) {
        Matrix res2 = SequentialGauss(matrix, rows, cols, vec, vecSize);
        ASSERT_EQ(res1, res2);
    }
}
TEST(Gauss_Vertical, 7x7x7) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int rows = 7, cols = 7, vecSize = 7;
    Matrix matrix;
    Matrix vec;
    Matrix res1, res2;
    if (procRank == 0) {
        matrix = RandomMatrix(rows, cols);
        vec = RandomMatrix(vecSize, 1);
    }
    res1 = ParallelGauss(matrix, rows, cols, vec, vecSize);
    if (procRank == 0) {
        Matrix res2 = SequentialGauss(matrix, rows, cols, vec, vecSize);
        ASSERT_EQ(res1, res2);
    }
}
TEST(Gauss_Vertical, 30x30x30) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int rows = 30, cols = 30, vecSize = 30;
    Matrix matrix;
    Matrix vec;
    Matrix res1, res2;
    if (procRank == 0) {
        matrix = RandomMatrix(rows, cols);
        vec = RandomMatrix(vecSize, 1);
    }
    res1 = ParallelGauss(matrix, rows, cols, vec, vecSize);
    if (procRank == 0) {
        Matrix res2 = SequentialGauss(matrix, rows, cols, vec, vecSize);
        ASSERT_EQ(res1, res2);
    }
}
TEST(Gauss_Vertical, 50x50x50) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int rows = 50, cols = 50, vecSize = 50;
    Matrix matrix;
    Matrix vec;
    Matrix res1, res2;
    if (procRank == 0) {
        matrix = RandomMatrix(rows, cols);
        vec = RandomMatrix(vecSize, 1);
    }
    res1 = ParallelGauss(matrix, rows, cols, vec, vecSize);
    if (procRank == 0) {
        Matrix res2 = SequentialGauss(matrix, rows, cols, vec, vecSize);
        ASSERT_EQ(res1, res2);
    }
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners &listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
