// Copyright 2020 Romanuyk Sergey
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include"./lex_str.h"
TEST(Parallel_Operations_MPI, Test1) {
    const_cast<char*>(str1) = "1";
    const_cast<char*>(str2) = "abcde";
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int res2 = getParallelComprasion(str1, str2);
    if (rank == 0) {
        int res1 = getComparisonLIN(str1, str2);
        ASSERT_EQ(res1, res2);
    }
}
TEST(Parallel_Operations_MPI, Test2) {
    const_cast<char*>(str1) = "abcdz";
    const_cast<char*>(str2) = "abcde";
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int res2 = getParallelComprasion(str1, str2);
    if (rank == 0) {
        int res1 = getComparisonLIN(str1, str2);
        ASSERT_EQ(res1, res2);
    }
}
TEST(Parallel_Operations_MPI, Test3) {
    const_cast<char*>(str1) = "aaabaaa";
    const_cast<char*>(str2) = "aaacaaa";
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int res2 = getParallelComprasion(str1, str2);
    if (rank == 0) {
        int res1 = getComparisonLIN(str1, str2);
        ASSERT_EQ(res1, res2);
    }
}
TEST(Parallel_Operations_MPI, Test4) {
    const_cast<char*>(str1) = "kzzzzzzz";
    const_cast<char*>(str2) = "zaaaaaaa";
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int res2 = getParallelComprasion(str1, str2);
    if (rank == 0) {
        int res1 = getComparisonLIN(str1, str2);
        ASSERT_EQ(res1, res2);
    }
}
TEST(Parallel_Operations_MPI, Test5) {
    const_cast<char*>(str1) = "FFFFFF";
    const_cast<char*>(str2) = "x";
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int res2 = getParallelComprasion(str1, str2);
    if (rank == 0) {
        int res1 = getComparisonLIN(str1, str2);
        ASSERT_EQ(res1, res2);
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
