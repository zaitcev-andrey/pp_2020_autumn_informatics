// Copyright 2020 Belik Julia
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <mpi.h>
#include <cmath>
#include <algorithm>
#include <functional>
#include "./IntegrationTrapez.h"

TEST(Parallel_Operations_MPI, Test_Square) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        std::function<double(double)>f = [](double x) {return x * x; };
        double i1 = getSequentialIntegration(f, 2, 5, 3);
        double i2 = getParallelIntegration(f, 2, 5, 3);
        ASSERT_EQ(i1, i2);
    }
}

TEST(Parallel_Operations_MPI, Test_Sin) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        std::function<double(double)>f = [](double x) {return sin(x); };
        double i1 = getSequentialIntegration(f, 0, 3, 10);
        double i2 = getParallelIntegration(f, 0, 3, 10);
        EXPECT_NEAR(i1, i2, 1e-2);
    }
}

TEST(Parallel_Operations_MPI, Test_Polyn) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        std::function<double(double)>f = [](double x) {return x * x * 5 + 2 * x - 10; };
        double i1 = getSequentialIntegration(f, 0, 10, 10);
        double i2 = getParallelIntegration(f, 0, 10, 10);
        EXPECT_NEAR(i1, i2, 1e-2);
    }
}

TEST(Parallel_Operations_MPI, Test_Sqrt_On_Big_Length) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        std::function<double(double)>f = [](double x) { return sqrt(x); };
        double i1 = getSequentialIntegration(f, 0, 1000, 100);
        double i2 = getParallelIntegration(f, 0, 1000, 100);
        EXPECT_NEAR(i1, i2, 1e-2);
    }
}

TEST(Parallel_Operations_MPI, Test_Sqrt_On_Little_Length) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        std::function<double(double)>f = [](double x) { return sqrt(x); };
        double i1 = getSequentialIntegration(f, 0, 9, 9);
        double i2 = getParallelIntegration(f, 0, 9, 9);
        EXPECT_NEAR(i1, i2, 1e-2);
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
