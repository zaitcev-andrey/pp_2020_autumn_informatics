// Copyright 2020 Zoreev Mikhail

#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <mpi.h>

#include "../../../modules/task_3/zoreev_m_moore_algorithm/moore_algorithm.h"

void testGraph(size_t size, uint64_t *seqential_result, uint64_t *parallel_result) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int64_t *graph = new int64_t[size * size];
    if (rank == 0) {
        randomCompleteGraph(size, graph);
        double begin_time = MPI_Wtime();
        seqential_result = mooreAlgorithm(size, graph, 0);
        double end_time = MPI_Wtime();
        std::cout << "Seqential: " << end_time - begin_time << std::endl;
    }
    MPI_Bcast(graph, static_cast<int>(size * size), MPI_UINT64_T, 0, MPI_COMM_WORLD);
    double begin_time = MPI_Wtime();
    parallel_result = mooreAlgorithmParallel(size, graph, 0);
    double end_time = MPI_Wtime();
    if (rank == 0) {
        std::cout << "Parallel: " << end_time - begin_time << std::endl;
    }
    delete[] graph;
}

TEST(Moore_Algotithm_MPI, SpeedAndQualtiyTestTemplate) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    size_t size = 8;
    int64_t *graph = new int64_t[size * size];
    uint64_t *seqential_result = nullptr;
    if (rank == 0) {
        randomCompleteGraph(size, graph);
        printGraph(size, graph);  // <- Disable at large size
        double begin_time = MPI_Wtime();
        seqential_result = mooreAlgorithm(size, graph, 0);
        double end_time = MPI_Wtime();
        std::cout << "Seqential: " << end_time - begin_time << std::endl;
        printPredecessor(size, seqential_result);  // <- Disable at large size
    }
    MPI_Bcast(graph, static_cast<int>(size * size), MPI_UINT64_T, 0, MPI_COMM_WORLD);
    double begin_time = MPI_Wtime();
    uint64_t *parallel_result = mooreAlgorithmParallel(size, graph, 0);
    double end_time = MPI_Wtime();
    if (rank == 0) {
        std::cout << "Parallel: " << end_time - begin_time << std::endl;
        printPredecessor(size, parallel_result);  // <- Disable at large size
        for (size_t i = 0; i < size; i++) {
            ASSERT_EQ(seqential_result[i], parallel_result[i]);
        }
        delete[] seqential_result;
    }

    delete[] graph;
    delete[] parallel_result;
}

TEST(Moore_Algotithm_MPI, TestCompleGraph8) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    size_t size = 8;
    uint64_t *seqential_result = nullptr, *parallel_result = nullptr;
    testGraph(size, seqential_result, parallel_result);
    if (rank == 0) {
        for (size_t i = 0; i < size; i++) {
            ASSERT_EQ(seqential_result[i], parallel_result[i]);
        }
    }
    delete[] seqential_result;
    delete[] parallel_result;
}

TEST(Moore_Algotithm_MPI, TestCompleGraph16) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    size_t size = 16;
    uint64_t *seqential_result = nullptr, *parallel_result = nullptr;
    testGraph(size, seqential_result, parallel_result);
    if (rank == 0) {
        for (size_t i = 0; i < size; i++) {
            ASSERT_EQ(seqential_result[i], parallel_result[i]);
        }
    }
    delete[] seqential_result;
    delete[] parallel_result;
}

TEST(Moore_Algotithm_MPI, TestCompleGraph32) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    size_t size = 32;
    uint64_t *seqential_result = nullptr, *parallel_result = nullptr;
    testGraph(size, seqential_result, parallel_result);
    if (rank == 0) {
        for (size_t i = 0; i < size; i++) {
            ASSERT_EQ(seqential_result[i], parallel_result[i]);
        }
    }
    delete[] seqential_result;
    delete[] parallel_result;
}

TEST(Moore_Algotithm_MPI, TestCompleGraph64) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    size_t size = 8;
    uint64_t *seqential_result = nullptr, *parallel_result = nullptr;
    testGraph(size, seqential_result, parallel_result);
    if (rank == 0) {
        for (size_t i = 0; i < size; i++) {
            ASSERT_EQ(seqential_result[i], parallel_result[i]);
        }
    }
    delete[] seqential_result;
    delete[] parallel_result;
}

TEST(Moore_Algotithm_MPI, TestCompleGraph100) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    size_t size = 8;
    uint64_t *seqential_result = nullptr, *parallel_result = nullptr;
    testGraph(size, seqential_result, parallel_result);
    if (rank == 0) {
        for (size_t i = 0; i < size; i++) {
            ASSERT_EQ(seqential_result[i], parallel_result[i]);
        }
    }
    delete[] seqential_result;
    delete[] parallel_result;
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners &listeners = ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
