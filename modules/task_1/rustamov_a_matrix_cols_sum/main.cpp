// Copyright 2020 Rustamov Azer
#include <mpi.h>
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include "./matrix_sum.h"

TEST(Parallel_Matrix_Cols_Sum, Size_0x0) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int rows = 0, cols = 0;
    Matrix matrix;
    if (procRank == 0)
        matrix = RandomMatrix(rows, cols);
    ASSERT_ANY_THROW(ParallelColsSum(matrix, rows, cols));
}
TEST(Parallel_Matrix_Cols_Sum, Size_100x100) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int rows = 100, cols = 100;
    Matrix matrix;
    if (procRank == 0)
         matrix = RandomMatrix(rows, cols);
    int sum = ParallelColsSum(matrix, rows, cols);
    if (procRank == 0) {
        int controlSum = SequentialColsSum(matrix);
        ASSERT_EQ(controlSum, sum);
    }
}

TEST(Parallel_Matrix_Cols_Sum, Size_92x1) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int rows = 92, cols = 1;
    Matrix matrix;
    if (procRank == 0)
        matrix = RandomMatrix(rows, cols);
    int sum = ParallelColsSum(matrix, rows, cols);
    if (procRank == 0) {
        int controlSum = SequentialColsSum(matrix);
        ASSERT_EQ(controlSum, sum);
    }
}

TEST(Parallel_Matrix_Cols_Sum, Size_1x35) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int rows = 1, cols = 35;
    Matrix matrix;
    if (procRank == 0)
        matrix = RandomMatrix(rows, cols);
    int sum = ParallelColsSum(matrix, rows, cols);
    if (procRank == 0) {
        int controlSum = SequentialColsSum(matrix);
        ASSERT_EQ(controlSum, sum);
    }
}

TEST(Parallel_Matrix_Cols_Sum, Size_77x58) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int rows = 77, cols = 58;
    Matrix matrix;
    if (procRank == 0)
        matrix = RandomMatrix(rows, cols);
    int sum = ParallelColsSum(matrix, rows, cols);
    if (procRank == 0) {
        int controlSum = SequentialColsSum(matrix);
        ASSERT_EQ(controlSum, sum);
    }
}

TEST(Parallel_Matrix_Cols_Sum, Size_58x77) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int rows = 58, cols = 77;
    Matrix matrix;
    if (procRank == 0)
        matrix = RandomMatrix(rows, cols);
    int sum = ParallelColsSum(matrix, rows, cols);
    if (procRank == 0) {
        int controlSum = SequentialColsSum(matrix);
        ASSERT_EQ(controlSum, sum);
    }
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners &listeners = ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
