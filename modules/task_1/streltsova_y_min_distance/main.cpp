// Copyright 2020 Streltsova Yana
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./min_distance.h"

TEST(Parallel_Operations_MPI, Test_VecInt4) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int size_vector = 4;

    if (rank == 0) {
        global_vec = getRandomVector(size_vector);
    }

    int global_min = getParallelOperations(global_vec, size_vector);

    if (rank == 0) {
        int min_idx = getSequentialOperations(global_vec, size_vector);
        ASSERT_EQ(min_idx, global_min);
    }
}

TEST(Parallel_Operations_MPI, Test_VecInt13) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int size_vector = 13;

    if (rank == 0) {
        global_vec = getRandomVector(size_vector);
    }

    int global_min = getParallelOperations(global_vec, size_vector);

    if (rank == 0) {
        int min_idx = getSequentialOperations(global_vec, size_vector);
        ASSERT_EQ(min_idx, global_min);
    }
}

TEST(Parallel_Operations_MPI, Test_VecInt157) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int size_vector = 157;

    if (rank == 0) {
        global_vec = getRandomVector(size_vector);
    }

    int global_min = getParallelOperations(global_vec, size_vector);

    if (rank == 0) {
        int min_idx = getSequentialOperations(global_vec, size_vector);
        ASSERT_EQ(min_idx, global_min);
    }
}

TEST(Parallel_Operations_MPI, Test_VecInt1007) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int size_vector = 1007;

    if (rank == 0) {
        global_vec = getRandomVector(size_vector);
    }

    int global_min = getParallelOperations(global_vec, size_vector);

    if (rank == 0) {
        int min_idx = getSequentialOperations(global_vec, size_vector);
        ASSERT_EQ(min_idx, global_min);
    }
}

TEST(Parallel_Operations_MPI, Test_VecInt5136) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> global_vec;
    const int size_vector = 3936;

    if (rank == 0) {
        global_vec = getRandomVector(size_vector);
    }

    int global_min = getParallelOperations(global_vec, size_vector);

    if (rank == 0) {
        int min_idx = getSequentialOperations(global_vec, size_vector);
        ASSERT_EQ(min_idx, global_min);
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
