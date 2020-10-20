#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "matrix_columns_sum.h"

// 1
TEST(Parallel_Operations_MPI, Matrix_20_20)
{
    int rank, processes_count;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);

    const int count_columns = 20, count_raws = 20;

    std::vector<int> test_matrix(count_columns * count_raws);
    int offset = int(ceil(test_matrix.size() / processes_count));

    if (rank == 0)
    {
        test_matrix = generateRandomMatrix(count_raws, count_columns);
    }

    std::vector<int> parallel_sum_cols = getParallelColumnsSum(test_matrix, count_columns, count_raws);

    if (rank == 0)
    {
        std::vector<int> sequential_sum = getSequentialColumnsSum(test_matrix, count_columns, count_raws,
                                                                  processes_count, rank, offset);
        ASSERT_EQ(parallel_sum_cols, sequential_sum);
    }
}

// 2
TEST(Parallel_Operations_MPI, Matrix_50_25)
{
    int rank, processes_count;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);

    int count_columns = 50, count_raws = 25;

    std::vector<int> test_matrix(count_columns * count_raws);
    int offset = int(ceil(test_matrix.size() / processes_count));

    if (rank == 0)
    {
        test_matrix = generateRandomMatrix(count_raws, count_columns);
    }

    std::vector<int> parallel_sum_cols = getParallelColumnsSum(test_matrix, count_columns, count_raws);

    if (rank == 0)
    {
        std::vector<int> sequential_sum = getSequentialColumnsSum(test_matrix, count_columns, count_raws,
                                                                  processes_count, rank, offset);
        ASSERT_EQ(parallel_sum_cols, sequential_sum);
    }
}


// 3
TEST(Parallel_Operations_MPI, Matrix_10_5)
{
    int rank, processes_count;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);

    int count_columns = 10, count_raws = 5;

    std::vector<int> test_matrix(count_columns * count_raws);
    int offset = int(ceil(test_matrix.size() / processes_count));

    if (rank == 0)
    {
        test_matrix = generateRandomMatrix(count_raws, count_columns);
    }

    std::vector<int> parallel_sum_cols = getParallelColumnsSum(test_matrix, count_columns, count_raws);

    if (rank == 0)
    {
        std::vector<int> sequential_sum = getSequentialColumnsSum(test_matrix, count_columns, count_raws,
                                                                  processes_count, rank, offset);
        ASSERT_EQ(parallel_sum_cols, sequential_sum);
    }
}

//4
TEST(Parallel_Operations_MPI, Matrix_60_61)
{
    int rank, processes_count;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);

    int count_columns = 60, count_raws = 61;

    std::vector<int> test_matrix(count_columns * count_raws);
    int offset = int(ceil(test_matrix.size() / processes_count));

    if (rank == 0)
    {
        test_matrix = generateRandomMatrix(count_raws, count_columns);
    }

    std::vector<int> parallel_sum_cols = getParallelColumnsSum(test_matrix, count_columns, count_raws);

    if (rank == 0)
    {
        std::vector<int> sequential_sum = getSequentialColumnsSum(test_matrix, count_columns, count_raws,
                                                              processes_count, rank, offset);
        ASSERT_EQ(parallel_sum_cols, sequential_sum);
    }
}

//5
TEST(Parallel_Operations_MPI, Matrix_1_10)
{
    int rank, processes_count;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);

    int count_columns = 1, count_raws = 10;

    std::vector<int> test_matrix(count_columns * count_raws);
    int offset = int(ceil(test_matrix.size() / processes_count));

    if (rank == 0)
    {
        test_matrix = generateRandomMatrix(count_raws, count_columns);
    }

        std::vector<int> parallel_sum_cols = getParallelColumnsSum(test_matrix, count_columns, count_raws);

    if (rank == 0)
    {
        std::vector<int> sequential_sum = getSequentialColumnsSum(test_matrix, count_columns, count_raws,
                                                              processes_count, rank, offset);
        ASSERT_EQ(parallel_sum_cols, sequential_sum);
    }
}

//6
TEST(Parallel_Operations_MPI, Matrix_50_1)
{
    int rank, processes_count;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);

    int count_columns = 50, count_raws = 1;

    std::vector<int> test_matrix(count_columns * count_raws);
    int offset = int(ceil(test_matrix.size() / processes_count));

    if (rank == 0)
    {
        test_matrix = generateRandomMatrix(count_raws, count_columns);
    }

    std::vector<int> parallel_sum_cols = getParallelColumnsSum(test_matrix, count_columns, count_raws);

    if (rank == 0)
    {
        std::vector<int> sequential_sum = getSequentialColumnsSum(test_matrix, count_columns, count_raws,
                                                              processes_count, rank, offset);
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