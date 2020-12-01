// Copyright 2020 Kasyanychev Mikhail
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <mpi.h>
#include "./producer_consumers.h"

TEST(Parallel_Operations_MPI, Test_1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int nums[4] = { 4, 36, 9, 16 };
    double roots[4];
    double real_roots[4] = { 2, 6, 3, 4 };
    sqrNum(nums, roots, 4);
    bool flag = true;

    for (int i = 0; i < 4; i++) {
        if (roots[i] != real_roots[i]) {
            flag = false;
            break;
        }
    }

    if (rank == 0) {
        EXPECT_TRUE(flag);
    }
}

TEST(Parallel_Operations_MPI, Test_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int nums[4] = { 0, 1, 2, 3 };
    int* test_nums = generateNum(4);
    bool flag = true;

    for (int i = 0; i < 4; i++) {
        if (nums[i] != test_nums[i]) {
            flag = false;
            break;
        }
    }
    if (rank == 0) {
        EXPECT_TRUE(flag);
    }
}

TEST(Parallel_Operations_MPI, Test_3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int nums[4] = { 4, 9, 16, 36 };
    double roots[4];

    double real_roots[4];
    sqrNum(nums, real_roots, 4);

    producerConsumers(nums, roots, 4);

    bool flag = true;

    for (int i = 0; i < 4; i++) {
        if (roots[i] != real_roots[i]) {
            flag = false;
            break;
        }
    }
    if (rank == 0) {
        EXPECT_TRUE(flag);
    }
}

TEST(Parallel_Operations_MPI, Test_4) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int nums[4] = { 16, 16, 9, 36 };
    double roots[4];
    double real_roots[4] = { 2, 4, 3, 6 };

    producerConsumers(nums, roots, 4);

    bool flag = true;

    for (int i = 0; i < 4; i++) {
        if (roots[i] != real_roots[i]) {
            flag = false;
            break;
        }
    }
    if (rank == 0) {
        EXPECT_FALSE(flag);
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
