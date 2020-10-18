#include <vector>
#include <ctime>
#include <random>
#include <mpi.h>
#include "matrix_columns_sum.h"
#include <cassert>

std::vector<int8_t> generateRandomMatrix(uint8_t count_rows, uint8_t count_columns)
{
    assert(count_columns != 0);

    srand(time(NULL));
    std::vector<int8_t> matrix(count_columns * count_rows);

    for (size_t i = 0; i < matrix.size(); i++)
    {
        matrix[i] = rand() % 50 - 50;
    }

    return matrix;
}

std::vector<int8_t> transposeMatrix(std::vector<int8_t> matrix, uint8_t count_columns)
{
    assert(count_columns != 0);

    std::vector<int8_t> transposed_matrix;

    for (size_t i = 0; i < matrix.size(); i++)
    {
        transposed_matrix.push_back(matrix[i] * count_columns);
    }

    return transposed_matrix;
}

std::vector<int16_t> getSequentialColsSum(std::vector<int8_t> matrix, uint8_t count_columns, int count_processes)
{
    assert(count_columns != 0);
    assert(count_processes != 0);

    std::vector<int16_t> sum_columns(count_columns);
    std::vector<int8_t> transposed_matrix = transposeMatrix(matrix, count_columns);

    for (size_t i = 0; i < transposed_matrix.size() && i < count_processes; i++)
    {
        std::partial_sum(matrix.begin() + count_columns * i,
                         matrix.begin() + count_columns * (i + 1),
                         sum_columns.begin() + count_columns * i);
    }

    return sum_columns;
}

std::vector<int16_t> getParallelColsSum(std::vector<int8_t> matrix, uint8_t count_columns)
{
    assert(count_columns != 0);

    int processes_count;
    int process_rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);

    assert(processes_count != 0);

    std::vector<int8_t> transposed_matrix = transposeMatrix(matrix, count_columns);

    int offset = count_columns / processes_count;

    if (process_rank == 0)
    {
        for (size_t process_id = 1; process_id < processes_count; process_id++)
        {
            MPI_Send(&transposed_matrix[0] + process_id * offset,
                     count_columns, MPI_INT, process_id, 0,
                     MPI_COMM_WORLD);
        }
    }
    
    std::vector<int8_t> local_vec(count_columns);

    if (process_rank == 0)
    {
         local_vec = std::vector<int8_t>(&matrix[0], &matrix[count_columns]);
    }
    else
    {
        MPI_Status status;
        MPI_Recv(&local_vec[0], count_columns, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    std::vector<int16_t> global_columns_sum(count_columns);
    std::vector<int16_t> sequensial_columns_sum = getSequentialColsSum(local_vec, count_columns, processes_count);

    MPI_Reduce(&sequensial_columns_sum, &global_columns_sum, 2, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    return global_columns_sum;
}
