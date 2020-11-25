// Copyright 2020 Gruzdeva Diana
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "./mat_mult_horiz_only.h"

TEST(Parallel_Operations_MPI, MATRICES_10x10) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<int> a;
    std::vector<int> b;

    int size = 10;

    if (rank == 0) {
        a = getRandomMatrix(size, size, time(0));
        b = getRandomMatrix(size, size, time(0) + 1);
    }

    std::vector<int> parallel_result = getParallelMultiplication(a, b, size);

    if (rank == 0) {
        std::vector<int> sequential_result = getSequentialMultiplication(a, b, size);
        ASSERT_EQ(sequential_result, parallel_result);
    }
}

TEST(Parallel_Operations_MPI, MATRICES_25x25) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<int> a;
    std::vector<int> b;

    int size = 25;

    if (rank == 0) {
        a = getRandomMatrix(size, size, time(0));
        b = getRandomMatrix(size, size, time(0) + 1);
    }

    std::vector<int> parallel_result = getParallelMultiplication(a, b, size);

    if (rank == 0) {
        std::vector<int> sequential_result = getSequentialMultiplication(a, b, size);
        ASSERT_EQ(sequential_result, parallel_result);
    }
}

TEST(Parallel_Operations_MPI, MATRICES_75x75) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<int> a;
    std::vector<int> b;

    int size = 75;

    if (rank == 0) {
        a = getRandomMatrix(size, size, time(0));
        b = getRandomMatrix(size, size, time(0) + 1);
    }

    std::vector<int> parallel_result = getParallelMultiplication(a, b, size);

    if (rank == 0) {
        std::vector<int> sequential_result = getSequentialMultiplication(a, b, size);
        ASSERT_EQ(sequential_result, parallel_result);
    }
}

TEST(Parallel_Operations_MPI, MATRICES_100x100) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<int> a;
    std::vector<int> b;

    int size = 100;

    if (rank == 0) {
        a = getRandomMatrix(size, size, time(0));
        b = getRandomMatrix(size, size, time(0) + 1);
    }

    std::vector<int> parallel_result = getParallelMultiplication(a, b, size);

    if (rank == 0) {
        std::vector<int> sequential_result = getSequentialMultiplication(a, b, size);
        ASSERT_EQ(sequential_result, parallel_result);
    }
}


TEST(Parallel_Operations_MPI, MATRICES_240x240) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<int> a;
    std::vector<int> b;

    int size = 240;

    if (rank == 0) {
        a = getRandomMatrix(size, size, time(0));
        b = getRandomMatrix(size, size, time(0) + 1);
    }

    std::vector<int> parallel_result = getParallelMultiplication(a, b, size);

    if (rank == 0) {
        std::vector<int> sequential_result = getSequentialMultiplication(a, b, size);
        ASSERT_EQ(sequential_result, parallel_result);
    }
}

int main(int argc, char** argv) {
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
