// Copyright 2020 Volkova Anastasia
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./sents_mpi.h"

TEST(Parallel_MPI, Test_Sentences_Length_100) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<char> global_sentence;
    const int count_size_sentence = 100;
    if (rank == 0) {
        global_sentence = getRandomLine(count_size_sentence);
    }

    int global_sum_sentences = getParallelOperations(global_sentence, count_size_sentence);
    if (rank == 0) {
        int reference_sum_sentences = getSequentialOperations(global_sentence);
        ASSERT_EQ(reference_sum_sentences, global_sum_sentences);
    }
}

TEST(Parallel_MPI, Test_Sentences_Length_200) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<char> global_sentence;
    const int count_size_sentence = 200;
    if (rank == 0) {
        global_sentence = getRandomLine(count_size_sentence);
    }

    int global_sum_sentences = getParallelOperations(global_sentence, count_size_sentence);
    if (rank == 0) {
        int reference_sum_sentences = getSequentialOperations(global_sentence);
        ASSERT_EQ(reference_sum_sentences, global_sum_sentences);
    }
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
