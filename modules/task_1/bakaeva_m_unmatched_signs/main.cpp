//Copyright 2020 Bakaeva Maria
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include "./unmached_signs.h"

/*TEST(UnmatchedSigns, NormalSize) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int size = 4;
    char* str1;
    char* str2;
    
    if (rank == 0) {
        str1 = generateString(size);
        printf(str1);
        std::cout << std::endl;
        str2 = generateString(size);
        printf(str2);
        std::cout << std::endl;
    }

    int parallelCount = getParallelUnmachedSignsCount(str1, str2);

    if (rank == 0) {
        int linearCount = getSequentialUnmachedSignsCount(str1, str2);
        ASSERT_EQ(linearCount, parallelCount);
    }
}*/

TEST(UnmatchedSigns, myExample) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int parallelCount = getParallelUnmachedSignsCount("abcd", "abcy");


    if (rank == 0) {
        int linearCount = getSequentialUnmachedSignsCount("abcd", "abcy");
        std::cout << std::endl << linearCount << "     " << parallelCount << std::endl;
        ASSERT_EQ(linearCount, parallelCount);
    }
}

TEST(UnmatchedSigns, equalsStrings) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int parallelCount = getParallelUnmachedSignsCount("abcd", "abcd");
    std::cout << parallelCount;

    if (rank == 0) {
        int linearCount = getSequentialUnmachedSignsCount("abcd", "abcd");
        std::cout << std::endl << linearCount << "     " << parallelCount << std::endl;
        ASSERT_EQ(linearCount, parallelCount);
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