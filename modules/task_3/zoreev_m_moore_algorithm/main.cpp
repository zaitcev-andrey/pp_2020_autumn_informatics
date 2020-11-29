// Copyright 2020 Zoreev Mikhail

#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <mpi.h>

#include "../../../modules/task_3/zoreev_m_moore_algorithm/moore_algorithm.h"

TEST(Moore_Algotithm_MPI, Graph_4) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    size_t size = 6;
    int64_t *graph = new int64_t[size * size];
    size_t *seqential_result = nullptr;
    if (rank == 0) {
        randomCompleteGraph(size, graph);
        printGraph(size, graph);
        seqential_result = mooreAlgorithm(size, graph, 0);
        printPredecessor(size, seqential_result);
    }
    MPI_Bcast(graph, size * size, MPI_UINT64_T, 0, MPI_COMM_WORLD);
    size_t *parallel_result = mooreAlgorithmParallel(size, graph, 0);
    if (rank == 0) {
        printPredecessor(size, parallel_result);
        delete[] seqential_result;
    }
    delete[] graph;
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