#include <vector>
#include <ctime>
#include <random>
#include <mpi.h>
#include "matrix_columns_sum.h"
#include <cassert>

std::vector<int> generateRandomMatrix(int count_rows, int count_columns)
{
    assert(count_columns != 0);

    srand(time(NULL));
    std::vector<int> matrix(count_columns * count_rows);

    for (size_t i = 0; i < matrix.size(); i++)
    {
        matrix[i] = rand() % 50 - 50;
    }

    return matrix;
}

std::vector<int> transposeMatrix(std::vector<int> matrix, int count_columns)
{
    assert(count_columns != 0);

    std::vector<int> transposed_matrix;

    for (size_t i = 0; i < matrix.size(); i++)
    {
        transposed_matrix.push_back(matrix[i] * count_columns);
    }

    return transposed_matrix;
}

/*
 * 0 1 2 3
 * 4 5 6 7
 * 8 9 10 11
 *
 * 0 4 8
 * 1 5 9
 * 2 6 10
 * 3 7 11
 *
 * vector[0, 1, 2, 3] vector[...]
 *
 */

std::vector<int> getSequentialColumnsSum(std::vector<int> matrix, int count_columns,
                                             int count_rows, int count_processes)
{
    assert(count_processes != 0 && count_columns != 0 && count_columns != 0);

    std::vector<int> sum_columns(count_columns);

    if (count_processes == 1)
    {
        std::vector <int> transposed_matrix = transposeMatrix(matrix, count_columns);

        for (size_t i = 0; i < transposed_matrix.size(); i++)
        {
            std::partial_sum(matrix.begin() + count_rows * i,
                             matrix.begin() + count_rows * (i + 1),
                             sum_columns.begin() + i);
        }
    }
    else
    {
        int local_sum = 0;

        for (int element : matrix)
        {
            local_sum += element;
        }

        sum_columns.push_back(local_sum);
    }

    return sum_columns;
}

std::vector<int> getParallelColumnsSum(std::vector<int> matrix, int count_columns)
{
    assert(count_columns != 0);

    int processes_count;
    int process_rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);

    assert(processes_count != 0);

    std::vector<int> transposed_matrix = transposeMatrix(matrix, count_columns);


    int offset = int(ceil(transposed_matrix.size() / processes_count));

    if (process_rank == 0)
    {
        for (size_t process_id = 1; process_id < processes_count; process_id++)
        {
            MPI_Send(&transposed_matrix[0] + offset * process_id,
                     offset, MPI_INT, process_id, 0,
                     MPI_COMM_WORLD);
        }
    }
    
    std::vector<int> local_vec(offset, 0);

    if (process_rank == 0)
    {
         local_vec = std::vector<int>(&matrix[0], &matrix[0] + offset);
    }
    else
    {
        MPI_Status status;
        MPI_Recv(&local_vec[0], offset, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    std::vector<int> global_columns_sum(count_columns);
    std::vector<int> sequential_columns_sum = getSequentialColumnsSum(local_vec, offset, processes_count);

    MPI_Reduce(&sequential_columns_sum, &global_columns_sum, count_columns, MPI_INT, MPI_LOR, 0, MPI_COMM_WORLD);
    return global_columns_sum;
}
