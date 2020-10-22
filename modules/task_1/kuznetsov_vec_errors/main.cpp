#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./vec_mpi.h"

TEST(VEC_MPI, Successful_normalize_100_elem)
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vec;
    int vec_size = 100;
    vec = randV(vec_size);
    vecNormalize(vec);
    if (rank == 0)
    {
        int res = parallelVector(vec);
        ASSERT_EQ(res, 0);
    }
}

TEST(VEC_MPI, Successful_normalize_500_elem)
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vec;
    int vec_size = 500;
    vec = randV(vec_size);
    vecNormalize(vec);
    if (rank == 0)
    {
        int res = parallelVector(vec);
        ASSERT_EQ(res, 0);
    }
}

TEST(VEC_MPI, Successful_normalize_1000_elem)
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vec;
    int vec_size = 1000;
    vec = randV(vec_size);
    vecNormalize(vec);
    if (rank == 0)
    {
        int res = parallelVector(vec);
        ASSERT_EQ(res, 0);
    }
}

TEST(VEC_MPI, With_errors)
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vec;
    int vec_size = 100;
    vec = randV(vec_size);
    if (rank == 0)
    {
        int res = parallelVector(vec);
        ASSERT_NE(res, 0);
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