// Copyright 2020 Zhivaykin Daniil
#include <gtest-mpi-listener.hpp>
#include <gtest.h>
#include "./rectangle.h"
#include <cmath>

std::function<double(double)> funct = func;

TEST(Parallel_Operations_MPI, FROM_0_TO_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double p_res = parall_int(funct, 0, 2, 50);

    if (rank == 0) {
        double d_res = def_int(funct, 0, 2, 50);
        ASSERT_EQ(p_res, d_res);
    }
}

TEST(Parallel_Operations_MPI, FROM_0_TO_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double p_res = parall_int(funct, 0, 2, 500);

    if (rank == 0) {
        double d_res = def_int(funct, 0, 2, 500);
        ASSERT_EQ(p_res, d_res);
    }
}

TEST(Parallel_Operations_MPI, FROM_0_TO_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double p_res = parall_int(funct, 0, 2, 1000);

    if (rank == 0) {
        double d_res = def_int(funct, 0, 2, 1000);
        ASSERT_EQ(p_res, d_res);
    }
}

TEST(Parallel_Operations_MPI, FROM_0_TO_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double p_res = parall_int(funct, 0, 2, 5000);

    if (rank == 0) {
        double d_res = def_int(funct, 0, 2, 5000);
        ASSERT_EQ(p_res, d_res);
    }
}

TEST(Parallel_Operations_MPI, ) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double p_res = parall_int(funct, 0, 1, 10000);

    if (rank == 0) {
        double d_res = def_int(funct, 0, 1, 10000);
        ASSERT_EQ(p_res, d_res);
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