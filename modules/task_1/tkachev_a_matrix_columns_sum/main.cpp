#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "matrix_columns_sum.h"

// 1
TEST(Parallel_Operations_MPI, Matrix_20_20)
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<int8_t> test_matrix;
    const uint8_t count_columns = 20, count_raws = 20;

    if (rank == 0)
    {
        test_matrix = generateRandomMatrix(count_raws, count_columns);
    }

    int16_t parallel_sum_cols = getParallelColsSum(test_matrix, count_columns);
    int16_t sequential_sum = 0;

    if (rank == 0)
    {
        sequential_sum = getSequentialColsSum(test_matrix, count_columns);
    }

    ASSERT_EQ(parallel_sum_cols, sequential_sum);
}

// 2
TEST(Parallel_Operations_MPI, Matrix_50_25)
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<int8_t> test_matrix;
    const uint8_t count_columns = 50, count_raws = 25;

    if (rank == 0)
    {
        test_matrix = generateRandomMatrix(count_raws, count_columns);
    }

    int16_t parallel_sum_cols = getParallelColsSum(test_matrix, count_columns);
    int16_t sequential_sum = 0;

    if (rank == 0)
    {
        sequential_sum = getSequentialColsSum(test_matrix, count_columns);
    }

    ASSERT_EQ(parallel_sum_cols, sequential_sum);
}


// 3
TEST(Parallel_Operations_MPI, Matrix_10_5)
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<int8_t> test_matrix;
    const uint8_t count_columns = 10, count_raws = 5;

    if (rank == 0)
    {
        test_matrix = generateRandomMatrix(count_raws, count_columns);
    }

    int16_t parallel_sum_cols = getParallelColsSum(test_matrix, count_columns);
    int16_t sequential_sum = 0;

    if (rank == 0)
    {
        sequential_sum = getSequentialColsSum(test_matrix, count_columns);
    }

    ASSERT_EQ(parallel_sum_cols, sequential_sum);
}

//4
TEST(Parallel_Operations_MPI, Matrix_60_61)
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<int8_t> test_matrix;
    const uint8_t count_columns = 60, count_raws = 61;

    if (rank == 0)
    {
    test_matrix = generateRandomMatrix(count_raws, count_columns);
    }

    int16_t parallel_sum_cols = getParallelColsSum(test_matrix, count_columns);
    int16_t sequential_sum = 0;

    if (rank == 0)
    {
    sequential_sum = getSequentialColsSum(test_matrix, count_columns);
    }

    ASSERT_EQ(parallel_sum_cols, sequential_sum);
}

//5
TEST(Parallel_Operations_MPI, Matrix_1_10)
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<int8_t> test_matrix;
    const uint8_t count_columns = 1, count_raws = 10;

    if (rank == 0)
    {
        test_matrix = generateRandomMatrix(count_raws, count_columns);
    }

    int16_t parallel_sum_cols = getParallelColsSum(test_matrix, count_columns);
    int16_t sequential_sum = 0;

    if (rank == 0)
    {
        sequential_sum = getSequentialColsSum(test_matrix, count_columns);
    }

    ASSERT_EQ(parallel_sum_cols, sequential_sum);
}

//6
TEST(Parallel_Operations_MPI, Matrix_50_1)
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<int8_t> test_matrix;
    const uint8_t count_columns = 50, count_raws = 1;

    if (rank == 0)
    {
        test_matrix = generateRandomMatrix(count_raws, count_columns);
    }

    int16_t parallel_sum_cols = getParallelColsSum(test_matrix, count_columns);
    int16_t sequential_sum = 0;

    if (rank == 0)
    {
        sequential_sum = getSequentialColsSum(test_matrix, count_columns);
    }

    ASSERT_EQ(parallel_sum_cols, sequential_sum);
}


int main(int argc, char** argv)
{
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