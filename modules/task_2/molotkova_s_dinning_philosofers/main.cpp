// Copyright 2020 Molotkova Svetlana
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <array>
#include "./Dinning_philosophers.h"

TEST(MPI_Philosofers, Test_ph) {
    int myRank, ProcSize = 10;
    MPI_Comm_size(MPI_COMM_WORLD, &ProcSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    ASSERT_NO_THROW(diningPhilosofers(myRank, ProcSize));
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
