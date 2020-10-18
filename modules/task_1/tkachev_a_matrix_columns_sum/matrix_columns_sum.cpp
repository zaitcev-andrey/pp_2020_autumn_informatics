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

int16_t getSequentialColsSum(std::vector<int8_t> matrix, uint8_t count_columns)
{
    int16_t cols_sum = 0;

    assert(count_columns != 0);

    for (size_t current_column = 0; current_column < count_columns; current_column++)
    {
        cols_sum += matrix[current_column + count_columns];
    }

    return cols_sum;
}

<<<<<<< HEAD
int16_t getParallelColsSum(std::vector<int8_t> matrix, uint8_t count_columns)
=======
int getParallelColsSum(std::vector<int8_t> matrix, uint8_t count_columns)
>>>>>>> 35f53f84d395a7ca5f9b1d2662d4232b8a8ee7e6
{
    assert(count_columns != 0);

    int processes_count;
    int process_rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);

<<<<<<< HEAD
    assert(processes_count != 0);

    uint8_t offset = count_columns / processes_count;

=======
>>>>>>> 35f53f84d395a7ca5f9b1d2662d4232b8a8ee7e6
    if (process_rank == 0)
    {
        for (size_t process_id = 1; process_id < processes_count; process_id++)
        {
<<<<<<< HEAD
            MPI_Send(&matrix[0] + process_id * offset,
=======
            MPI_Send(&matrix[0] + process_id * count_columns,
>>>>>>> 35f53f84d395a7ca5f9b1d2662d4232b8a8ee7e6
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

    int16_t global_sum = 0;

    int16_t sequensial_sum = getSequentialColsSum(local_vec, count_columns);

<<<<<<< HEAD
    MPI_Reduce(&sequensial_sum, &global_sum, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
=======
    MPI_Reduce(&sequensial_sum, &global_sum, 2, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
>>>>>>> 35f53f84d395a7ca5f9b1d2662d4232b8a8ee7e6
    return global_sum;
}
