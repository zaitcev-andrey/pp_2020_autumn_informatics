// Copyright 2020 Molotkova Svetlana
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <array>
#include "./Dinning_philosophers.h"

TEST(MPI_Philosofers, Test_ph_10) {
    int myRank, ProcSize;
    MPI_Comm_size(MPI_COMM_WORLD, &ProcSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    int time = 10;
    ASSERT_NO_THROW(diningPhilosofers(myRank, ProcSize, time));
}

TEST(MPI_Philosofers, Test_ph_15) {
    int myRank, ProcSize;
    MPI_Comm_size(MPI_COMM_WORLD, &ProcSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    int time = 15;
    ASSERT_NO_THROW(diningPhilosofers(myRank, ProcSize, time));
}

TEST(MPI_Philosofers, Test_ph_20) {
    int myRank, ProcSize;
    MPI_Comm_size(MPI_COMM_WORLD, &ProcSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    int time = 20;
    ASSERT_NO_THROW(diningPhilosofers(myRank, ProcSize, time));
}

TEST(MPI_Philosofers, Test_ph_30) {
    int myRank, ProcSize;
    MPI_Comm_size(MPI_COMM_WORLD, &ProcSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    int time = 30;
    ASSERT_NO_THROW(diningPhilosofers(myRank, ProcSize, time));
}

TEST(MPI_Philosofers, Test_ph_16) {
    int myRank, ProcSize;
    MPI_Comm_size(MPI_COMM_WORLD, &ProcSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    int time = 16;
    ASSERT_NO_THROW(diningPhilosofers(myRank, ProcSize, time));
}

TEST(MPI_Philosofers, Test_ph_11) {
    int myRank, ProcSize;
    MPI_Comm_size(MPI_COMM_WORLD, &ProcSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    int time = 11;
    ASSERT_NO_THROW(diningPhilosofers(myRank, ProcSize, time));
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    srand(time(NULL));
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);

    return RUN_ALL_TESTS();
}

