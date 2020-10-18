// Copyright 2020 Solovev Alexandr
#include <mpi.h>
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <string>
#include "./count_letters.h"

TEST(Parallel_Count_Letters_MPI, Size_1) {
    int process_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    int elements_count = 1;
    std::string result;
    if (process_rank == 0)
        result = CreateRandomString(elements_count);
    int sum = calculateCountParallel(result, elements_count);
    if (process_rank == 0) {
        int control_sum = calculateCountSequental(result);
        ASSERT_EQ(control_sum, sum);
    }
}

TEST(Parallel_Matrix_Sum_MPI, Size_1x1) {
    int process_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    int rows = 1;
    int cols = 1;
    int elements_count = rows * cols;
    std::string result;
    if (process_rank == 0)
        result = CreateRandomString(elements_count);
    int sum = calculateCountParallel(result, elements_count);
    if (process_rank == 0) {
        int control_sum = calculateCountSequental(result);
        ASSERT_EQ(control_sum, sum);
    }
}

TEST(Parallel_Matrix_Sum_MPI, Size_100x1) {
    int process_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    int rows = 100;
    int cols = 200;
    int elements_count = rows * cols;
    std::string result;
    if (process_rank == 0)
        result = CreateRandomString(elements_count);
    int sum = calculateCountParallel(result, elements_count);
    if (process_rank == 0) {
        int control_sum = calculateCountSequental(result);
        ASSERT_EQ(control_sum, sum);
    }
}

TEST(Parallel_Matrix_Sum_MPI, Size_100x200) {
    int process_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    int rows = 100;
    int cols = 200;
    int elements_count = rows * cols;
    std::string result;
    if (process_rank == 0)
        result = CreateRandomString(elements_count);
    int sum = calculateCountParallel(result, elements_count);
    if (process_rank == 0) {
        int control_sum = calculateCountSequental(result);
        ASSERT_EQ(control_sum, sum);
    }
}

TEST(Parallel_Matrix_Sum_MPI, Size_51x2) {
    int process_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    int rows = 51;
    int cols = 2;
    int elements_count = rows * cols;
    std::string result;
    if (process_rank == 0)
        result = CreateRandomString(elements_count);
    int sum = calculateCountParallel(result, elements_count);
    if (process_rank == 0) {
        int control_sum = calculateCountSequental(result);
        ASSERT_EQ(control_sum, sum);
    }
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
