// Copyright 2020 Tashirev Ivan
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>

#include "../../../modules/task_2/tashirev_i_horiz_scheme/RibbonHorizontalPattern.h"

TEST(Parallel_Operations_MPI, Test_Matrix100_10) {
    const int rows = 100;
    const int columns = 10;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> matr;
    std::vector<int> vec;
    if (rank == 0) {
        matr = getMatrix(rows, columns);
        vec = getVector(columns);
    }
    std::vector<int> multiply = multMatrixParallel(matr, rows, columns, vec, columns);
    if (rank == 0) {
        std::vector<int> multiplyNotParall = multMatrixSeq(matr, rows, columns, vec, columns);
        for (int i = 0; i < multiply.size(); i++)
            ASSERT_EQ(multiplyNotParall[i], multiply[i]);
    }
}

TEST(Parallel_Operations_MPI, Test_Matrix11_11) {
    const int rows = 11;
    const int columns = 11;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> matr;
    std::vector<int> vec;
    if (rank == 0) {
        matr = getMatrix(rows, columns);
        vec = getVector(columns);
    }
    std::vector<int> multiply = multMatrixParallel(matr, rows, columns, vec, columns);
    if (rank == 0) {
        std::vector<int> multiplyNotParall = multMatrixSeq(matr, rows, columns, vec, columns);
        for (int i = 0; i < multiply.size(); i++)
            ASSERT_EQ(multiplyNotParall[i], multiply[i]);
    }
}
TEST(Parallel_Operations_MPI, Test_Matrix50_5) {
    const int rows = 50;
    const int columns = 5;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> matr;
    std::vector<int> vec;
    if (rank == 0) {
        matr = getMatrix(rows, columns);
        vec = getVector(columns);
    }
    std::vector<int> multiply = multMatrixParallel(matr, rows, columns, vec, columns);
    if (rank == 0) {
        std::vector<int> multiplyNotParall = multMatrixSeq(matr, rows, columns, vec, columns);
        for (int i = 0; i < multiply.size(); i++)
            ASSERT_EQ(multiplyNotParall[i], multiply[i]);
    }
}
TEST(Parallel_Operations_MPI, Test_Matrix3_3) {
    const int rows = 3;
    const int columns = 3;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> matr;
    std::vector<int> vec;
    if (rank == 0) {
        matr = getMatrix(rows, columns);
        vec = getVector(columns);
    }
    std::vector<int> multiply = multMatrixParallel(matr, rows, columns, vec, columns);
    if (rank == 0) {
        std::vector<int> multiplyNotParall = multMatrixSeq(matr, rows, columns, vec, columns);
        for (int i = 0; i < multiply.size(); i++)
            ASSERT_EQ(multiplyNotParall[i], multiply[i]);
    }
}
TEST(Parallel_Operations_MPI, Test_Matrix5_4) {
    const int rows = 5;
    const int columns = 4;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> matr;
    std::vector<int> vec;
    if (rank == 0) {
        matr = getMatrix(rows, columns);
        vec = getVector(columns);
    }
    std::vector<int> multiply = multMatrixParallel(matr, rows, columns, vec, columns);
    if (rank == 0) {
        std::vector<int> multiplyNotParall = multMatrixSeq(matr, rows, columns, vec, columns);
        for (int i = 0; i < multiply.size(); i++)
            ASSERT_EQ(multiplyNotParall[i], multiply[i]);
    }
}
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);

    return RUN_ALL_TESTS();
}
