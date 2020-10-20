#include <vector>
#include <ctime>
#include <random>
#include <mpi.h>
#include "matrix_columns_sum.h"
#include <cassert>
#include <cmath>

std::vector<int> generateRandomMatrix(int count_rows, int count_columns)
{
    assert(count_columns != 0);
    assert(count_rows != 0);

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

std::vector<int> getSequentialColumnsSum(std::vector<int> vector, int count_columns,
                                             int count_rows, int count_processes, int process_id, int offset)
{
    assert(count_processes != 0);
    assert(count_columns != 0);
    assert(count_rows != 0);
    assert(offset != 0);
    assert(vector.size() != 0);

    std::vector<int> sum_columns(count_columns);

    /*
     * If count process == 1 we just calculate all the columns sums by one process
     * If count process more than 1 we create for each piece of memory block (offset) fixed vector with size = count_columns
     * even If a piece of memory has size less than count_columns, anyway we use vector with 4 elements
     * We need to locate new numbers from a piece of the memory so as they were located in original matrix to sum them in the end of program
     * We make offset for them to fill unused in this process numbers with zeros
     *
     * for instance: matrix [0 1 2 3  4 5 6 7  8 9 10 11]. So we have created 2 processes.
     * first of the processes gets numbers from 0 to 5, and the second one gets from 6 to 11.
     * So due to a result vector need to be with the size = 4, but we got size = 6, we cut it until it has size (head) = 4
     * and the tail of it we (2 elements) we add to another new vector.
     * After these operations we get 4 vectors [0 1 2 3] [4 5 0 0] [6 7 8 9] [10 11 0 0]. So, when we use MPI_SUM
     * it sums it all and the result is vector [0 + 4 + 6 + 10, 1 + 5 + 7 + 11, and so on] That's what we need.
     *
     * another situation and instance: the same matrix but we have created 6 processes.
     * so we got vectors like: process_1[0, 1, 0, 0], process_2[0, 0, 2, 3], process_3[4, 5, 0, 0], process_4[0, 0, 6, 7].. and so on
     * after summing it all we got the result vector which we need.
     *
     */

    if (count_processes == 1)
    {
        std::vector<int> transposed_matrix = transposeMatrix(vector, count_columns);

        for (size_t i = 0; i < count_columns; i++)
        {
            std::partial_sum(transposed_matrix.begin() + count_columns * i,
                             transposed_matrix.begin() + count_columns * (i + 1),
                             sum_columns.begin() + i);
        }
    }
    else
    {
        int current_row;
        // find the index of the row (current_row) that has the first number of the vector we have got
        for (current_row = 1; current_row < count_columns; current_row++)
        {
            if (process_id * offset < (current_row * count_columns - 1))
            {
                break;
            }
        }

        // if the length of the vector is larger than the row length we cut the vector in two parts: head and tail
        // the head is located in the row, where the first element is located, up to the end of the row
        // tail always is located in the next row after the current one
        if (process_id * offset + offset > count_columns * current_row)
        {
            static int head_size = count_columns * current_row - offset * process_id;
            std::vector<int> head = std::vector<int>(count_columns);
            std::vector<int> tail = std::vector<int>(count_columns);

            // if the first number of the vector isn't the start of the current row
            // if it is, we fill the empty elements with zeros up to the first element of the vector
            if (process_id * offset > count_columns * current_row)
            {
                for (size_t i = 0; i < process_id * offset; i++)
                    head.push_back(0);
            }

            for (size_t i = 0; i < head_size; i++)
                head.push_back(vector[i]);

            for (size_t i = head_size + 1; i < vector.size(); i++)
                tail.push_back(vector[i]);

            // fill with zeros empty elements of the tail until the next row after current ends
            while (process_id * offset + offset <= (current_row + 1) * count_columns)
                tail.push_back(0);

            for (size_t i = 0; i < count_columns; i++)
                sum_columns.push_back(head[i] + tail[i]);
        }
        else
        {
            if (process_id * offset > count_columns * current_row)
            {
                for (size_t i = 0; i < process_id * offset; i++)
                    sum_columns.push_back(0);
            }

            for (size_t i = 0; i < vector.size(); i++)
                sum_columns.push_back(vector[i]);
        }
    }

    return sum_columns;
}

std::vector<int> getParallelColumnsSum(std::vector<int> matrix, int count_columns, int count_rows)
{
    assert(count_columns != 0);
    assert(count_rows != 0);
    assert(matrix.size() != 0);

    int processes_count;
    int process_rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);

    assert(processes_count != 0);

    int offset = int(ceil(matrix.size() / processes_count));

    int memory_blocks_count = matrix.size() / offset;

    if (process_rank == 0)
    {
        for (size_t process_id = 1; process_id < processes_count && process_id < memory_blocks_count; process_id++)
        {
            MPI_Send(&matrix[0] + offset * process_id,
                     offset, MPI_INT, process_id, 0,
                     MPI_COMM_WORLD);
        }
    }
    
    std::vector<int> local_vec(offset);

    if (process_rank == 0)
    {
         local_vec = std::vector<int>(matrix.begin(), matrix.begin() + offset);
    }
    else
    {
        MPI_Status status;
        MPI_Recv(&local_vec[0], offset, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    std::vector<int> global_columns_sum(count_columns);
    std::vector<int> sequential_columns_sum = getSequentialColumnsSum(local_vec, count_columns, count_rows,
                                                                      processes_count, process_rank, offset);

    MPI_Reduce(&sequential_columns_sum, &global_columns_sum, count_columns, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    return global_columns_sum;
}