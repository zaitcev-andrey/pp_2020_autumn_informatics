#include <vector>
#include <ctime>
#include <random>
#include <mpi.h>
#include "matrix_columns_sum.h"
#include <cassert>
#include <cmath>
#include "math.h"
#include <iostream>

std::vector<int> generateRandomMatrix(int count_rows, int count_columns)
{
    assert(count_columns != 0);
    assert(count_rows != 0);

    srand(time(NULL));
    std::vector<int> matrix(count_rows * count_columns);

    for (int i = 0; i < matrix.size(); i++)
        matrix[i] = rand() % 100 - 50;

    return matrix;
}

std::vector<int> getSequentialColumnsSum(std::vector<int> vector, int count_columns,
                                         int count_rows, int count_processes, int process_id, int offset)
{
    assert(count_processes != 0);
    assert(count_columns != 0);
    assert(count_rows != 0);
    assert(offset != 0);
    assert(vector.size() != 0);

    std::vector<int> sum_columns;

    int check_sum = 0;
    for (int item : vector) check_sum += item;
    if (check_sum == 0) return std::vector<int>(count_columns, 0);

    /*
     * If count process == 1 we just calculate all the columns sums by one process, here the offset is matrix.size()
     * If count process more than 1 we create for each fixed piece of data (offset) fixed vector with size = count_columns
     * even If the offset has size less than count_columns, anyway we use vector with 4 elements
     * We need to locate new numbers from offsets so as they were located in original matrix to sum them in the end of program
     * or just to save proportions
     * unsed numbers in size4vectors we fill with zeros
     *
     * for instance: matrix [0 1 2 3  4 5 6 7  8 9 10 11]. So we have created 2 processes.
     * first of the processes gets numbers from 0 to 5, and the second one gets from 6 to 11.
     * So due to a result vector need to be with the size = 4, 
     * but we got vectors for each procces with size = 6, we cut it until it has size (head) = 4
     * and the tail of it we (2 elements) add to another new vector.
     * After these operations we get 4 vectors
     * [0 1 2 3](headVector1) [4 5 0 0](tailVector1) [6 7 8 9](headVector2) [10 11 0 0](tailVector2). 
     * So, when we use MPI_SUM it sums it all and the result is the vector [0 + 4 + 6 + 10, 1 + 5 + 7 + 11, and so on] 
     * That's what we need.
     *
     * another situation and an instance: the same matrix but we have created 6 processes (or more).
     * so we will get vectors like: process_1[0, 1, 0, 0], process_2[0, 0, 2, 3], process_3[4, 5, 0, 0], process_4[0, 0, 6, 7].. and so on
     * after summing it all we got the result vector which we need.
     * the difference from the first instance is that the offset < count_columns and therefore all the vectors of all the processes does not have tails
     * and each head equals their offset
     *
     * THE MAP OF A MATRIX (BY ID):
     * # let the first element of the given vector is located in the first row
     * 
     * 0 1 . . (process_id * offset <- first element of current process) . . . . . . . (count_columns * count_row - 2) (count_columns * current_row - 1)
     * (count_columns * current_row) (count_columns * current_row + 1) . . . (count_columns * 2 * current_row - 2) (count_columns * 2 * current_row - 1)
     * . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
     * . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . (matrix.size() - 1)
     */

    if (count_processes == 1)
    {
        for (int current_column = 0; current_column < count_columns; current_column++)
        {
            int local_column_sum = 0;

            for (int current_row = 0; current_row < count_rows; current_row++)
            {
                local_column_sum += vector[current_column + current_row * count_columns];
            }

            sum_columns.push_back(local_column_sum);
        }
    }
    else
    {
        // we understand that (process_id * offset) is the position of the first element of a process
        int current_row = 0;

        if (process_id * offset < count_columns)
        {
            current_row = 1;
        }
        else
        {
            // break when we find the row with the first element of the vector
            for (current_row = 2; current_row < count_rows; current_row++)
            {
                if (process_id * offset < current_row * count_columns) break;
            }
        }

        // if the length of the vector is larger than the row length we cut the vector in two parts: head and tail
        // the head is located in the row, where the first element is located, up to the end of the row
        // tail always is located in the next row after the current one
        if (process_id * offset + (offset-1) >= count_columns * current_row)
        {
            int head_size = count_columns * current_row - offset * process_id;
            std::vector<int> head;
            std::vector<int> tail(count_columns, 0);

            // if the first number of the vector isn't the start of the current row
            // if it is, we fill the empty elements with zeros up to the first element of the vector
     
            for (int i = 0; (count_columns * (current_row - 1) + i < process_id * offset) && 
                            (head_size < count_columns); i++){
                head.push_back(0);
            }
    
            for (int i = 0; i < head_size; i++)
                head.push_back(vector[i]);      

            for (int i = 0; i < count_columns; i++)
            {
                for (int j = 0; head_size + j * count_columns + i < vector.size(); j++)
                    tail[i] += vector[head_size + j * count_columns + i];   
            }

            for (int i = 0; i < count_columns; i++)
                sum_columns.push_back(head[i] + tail[i]);
        }
        else
        // no tail
        {
            // fill with zeros the start of the vector if it's necessary
            for (int i = 0; (count_columns * (current_row - 1) + i) < process_id * offset; i++)
            {
                sum_columns.push_back(0);
            }

            // we're sure the vector doens't have a tail
            for (int item : vector)
            {
                sum_columns.push_back(item);
            }
            
            // if the vector is have placed fully but the row isn't finished yet
            for (int i = 0; process_id * offset + (offset-1) + i < count_columns * current_row - 1; i++)
            {
                sum_columns.push_back(0);
            }
        }
    }

    return sum_columns;
}


std::vector<int> getParallelColumnsSum(std::vector<int> matrix, int count_columns, int count_rows)
{
    assert(count_columns != 0);
    assert(count_rows != 0);
    assert(matrix.size() != 0);
    assert(processes_count != 0);

    int processes_count, process_rank, offset, MAX_COUNT_PROCESS_TO_USE = 0;
    bool already_has_zeros = false;

    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);

    if (processes_count >= matrix.size())
    {
        MAX_COUNT_PROCESS_TO_USE = matrix.size(); 
        offset = 1;
    }
    else 
    {
        if (matrix.size() % processes_count != 0)
        {
            offset = round(matrix.size() / processes_count + 0.5);
        } 
        else
        { 
            if (matrix.size() % processes_count == 0)
            {
                offset = matrix.size() / processes_count;
            }
        }

        if (matrix.size() % 2 != 0)
        {
            MAX_COUNT_PROCESS_TO_USE = matrix.size(); 
            offset = 1;
        }
        else 
        {
            if (matrix.size() % 2 == 0)
            {
                MAX_COUNT_PROCESS_TO_USE = round(matrix.size() / offset + 0.5);
            }
        }
    }

    if (MAX_COUNT_PROCESS_TO_USE > processes_count)
    {
        bool already_has_zeros = true;
        offset = matrix.size();
        MAX_COUNT_PROCESS_TO_USE = 1;
        
        for (int i = 0; i < offset * processes_count; i++)
        {
            matrix.push_back(0);
        }
    }

    if (process_rank == 0)
    {
        if (MAX_COUNT_PROCESS_TO_USE <= processes_count || matrix.size() % processes_count != 0 && already_has_zeros == false)
        {
            for (int i = 0; i < offset * (processes_count - MAX_COUNT_PROCESS_TO_USE) + offset; i++)
            {
                matrix.push_back(0);
            }
        }
    }

    if (process_rank == 0)
    {
        for (int process_id = 1; process_id < processes_count; process_id++)
        {
            MPI_Send(&matrix[0] + offset * process_id, offset, 
                    MPI_INT, process_id, 0, MPI_COMM_WORLD);

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
   
    MPI_Reduce(sequential_columns_sum.data(), global_columns_sum.data(), 
               count_columns, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    return global_columns_sum;
}