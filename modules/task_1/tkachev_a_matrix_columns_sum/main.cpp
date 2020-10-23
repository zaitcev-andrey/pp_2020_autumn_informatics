#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "matrix_columns_sum.h"
#include <iostream>
#include "math.h"

TEST(Parallel_Operations_MPI, Matrix_20_20)
{
    int rank, processes_count;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);

    int count_columns = 14, count_rows = 3;
    std::vector<int> test_matrix(count_columns * count_rows);

    if (rank == 0)
    {
        test_matrix = generateRandomMatrix(count_rows, count_columns);
    }

    std::vector<int> parallel_sum_cols(count_columns);
    parallel_sum_cols = getParallelColumnsSum(test_matrix, count_columns, count_rows);

    if (rank == 0)
    {
        std::vector<int> sequential_sum(count_columns);
        sequential_sum = getSequentialColumnsSum(test_matrix, count_columns, count_rows,
                                                1, 0, test_matrix.size());
        ASSERT_EQ(parallel_sum_cols, sequential_sum);
    }
}

TEST(Parallel_Operations_MPI, Matrix_1_10)
{
    int rank, processes_count;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);

    int count_columns = 10, count_rows = 1;
    std::vector<int> test_matrix(count_columns * count_rows);

    if (rank == 0)
    {
        test_matrix = generateRandomMatrix(count_rows, count_columns);
    }

    std::vector<int> parallel_sum_cols(count_columns);
    parallel_sum_cols = getParallelColumnsSum(test_matrix, count_columns, count_rows);

    if (rank == 0)
    {
        std::vector<int> sequential_sum(count_columns);
        sequential_sum = getSequentialColumnsSum(test_matrix, count_columns, count_rows,
                                                1, 0, test_matrix.size());
        ASSERT_EQ(parallel_sum_cols, sequential_sum);
    }
}

TEST(Parallel_Operations_MPI, Matrix_31_1)
{
    int rank, processes_count;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);

    int count_columns = 1, count_rows = 31;
    std::vector<int> test_matrix(count_columns * count_rows);

    if (rank == 0)
    {
        test_matrix = generateRandomMatrix(count_rows, count_columns);
    }
    
    std::vector<int> parallel_sum_cols(count_columns);
    parallel_sum_cols = getParallelColumnsSum(test_matrix, count_columns, count_rows);

    if (rank == 0)
    {
        std::vector<int> sequential_sum(count_columns);
        sequential_sum = getSequentialColumnsSum(test_matrix, count_columns, count_rows,
                                                1, 0, test_matrix.size());
        ASSERT_EQ(parallel_sum_cols, sequential_sum);
    }
}

TEST(Parallel_Operations_MPI, Matrix_50_15)
{
    int rank, processes_count;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);

    int count_columns = 15, count_rows = 50;
    std::vector<int> test_matrix(count_columns * count_rows);

    if (rank == 0)
    {
        test_matrix = generateRandomMatrix(count_rows, count_columns);
    }

    std::vector<int> parallel_sum_cols(count_columns);
    parallel_sum_cols = getParallelColumnsSum(test_matrix, count_columns, count_rows);

    if (rank == 0)
    {
        std::vector<int> sequential_sum(count_columns);
        sequential_sum = getSequentialColumnsSum(test_matrix, count_columns, count_rows,
                                                1, 0, test_matrix.size());
        ASSERT_EQ(parallel_sum_cols, sequential_sum);
    }
}

TEST(Parallel_Operations_MPI, Matrix_21_20)
{
    int rank, processes_count;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);

    int count_columns = 20, count_rows = 21;
    std::vector<int> test_matrix(count_columns * count_rows);

    if (rank == 0)
    {
        test_matrix = generateRandomMatrix(count_rows, count_columns);
    }

    std::vector<int> parallel_sum_cols(count_columns);
    parallel_sum_cols = getParallelColumnsSum(test_matrix, count_columns, count_rows);

    if (rank == 0)
    {
        std::vector<int> sequential_sum(count_columns);
        sequential_sum = getSequentialColumnsSum(test_matrix, count_columns, count_rows,
                                                1, 0, test_matrix.size());
        ASSERT_EQ(parallel_sum_cols, sequential_sum);
    }
}

TEST(Parallel_Operations_MPI, Matrix_40_40)
{
    int rank, processes_count;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);

    int count_columns = 40, count_rows = 40;
    std::vector<int> test_matrix(count_columns * count_rows);

    if (rank == 0)
    {
        test_matrix = generateRandomMatrix(count_rows, count_columns);
    }

    std::vector<int> parallel_sum_cols(count_columns);
    parallel_sum_cols = getParallelColumnsSum(test_matrix, count_columns, count_rows);

    if (rank == 0)
    {
        std::vector<int> sequential_sum(count_columns);
        sequential_sum = getSequentialColumnsSum(test_matrix, count_columns, count_rows,
                                                1, 0, test_matrix.size());
        ASSERT_EQ(parallel_sum_cols, sequential_sum);
    }
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