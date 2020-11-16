// Copyright 2020 Kolesin Andrey
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <stdio.h>
#include <random>
#include <vector>
#include "./bubblesort.h"

TEST(Count_Words, Test_12) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> arr = {20,40,99};
    parallelSort(&arr);
    if (rank == 0) {
        EXPECT_EQ(arr, std::vector<int>({20,40,99}));
    }
}
TEST(Count_Words, Test_Random) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> arr = getRandomArray();
    std::vector<int> arr2 = arr;
    
    if (rank == 0) {
        double t1 = MPI_Wtime();
        parallelSort(&arr);
        double t2 = MPI_Wtime();
        SortMass(&arr2[0],arr2.size());
        double t3 =  MPI_Wtime();
        std::cout<<"TTTT: "<<t3-t2<<"    "<<t2-t1<<std::endl;
        EXPECT_EQ(arr, arr2);
    }
    else{
        std::vector<int> a = {};
        parallelSort(&a);
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
