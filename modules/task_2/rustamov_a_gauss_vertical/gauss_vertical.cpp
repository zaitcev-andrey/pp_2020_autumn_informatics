// Copyright 2020 Rustamov Azer
//#include <mpi.h>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <math.h>
#include <iomanip>
#include "../../../modules/task_2/rustamov_a_gauss_vertical/gauss_vertical.h"


Matrix RandomMatrix(int rows, int cols) {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_real_distribution<> rnd(-30.0 , 30.0);
    Matrix matrix(rows * cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i * cols + j] = static_cast<double>(rnd(mersenne));
        }
    }
    return matrix;
}

Matrix SequentialGauss(const Matrix& matrix, int rows, int cols,
    const Matrix& vec, int vector_size) {
    if ((rows != vector_size) || (rows != cols)) {
        throw("Invalid size");
    }
    Matrix temp_matrix(rows, cols);
    Matrix temp_vector(rows);
    temp_vector = vec;
    temp_matrix = matrix;
    std::vector<double> coefs(rows);
    std::vector<double> result(rows);
    std::vector<bool> was_pivot(rows);
    std::vector<int> pivot_order(rows);
    std::fill(was_pivot.begin(), was_pivot.end(), false);
    double d;
    // Прямой ход
    for (int current_col = 0; current_col < cols - 1; current_col++) {
        // Найти максимум по модулю в столбце
        double max = 0.0;
        int max_i = 0;
        for (int i = 0; i < rows; i++) {
            if ((fabs(temp_matrix[i * cols + current_col]) >= fabs(max))&&(!was_pivot[i])) {
                max = temp_matrix[i * cols + current_col];
                max_i = i;
            }
        }
        if (max == 0.0)
        {
            throw("Singular matrix");
        }
        was_pivot[max_i] = true;
        pivot_order[current_col] = max_i;
        // Подсчитать коэффиценты
        for (int k = 0; k < rows; k++) {
            coefs[k] = double(0);
            if (!was_pivot[k]) {
                coefs[k] = double(temp_matrix[k * cols + current_col]) /
                            double(temp_matrix[max_i * cols + current_col]);
            }
        }
        // Вычесть ведущую строку из остальных
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (!was_pivot[row]) {
                    temp_matrix[row * cols + col] -= double(temp_matrix[max_i * cols + col]) *
                        double(coefs[row]);
                    // Повторить для вектора b
                    temp_vector[row] -= double(temp_vector[max_i]) * double(coefs[row]);
                }
            }
        }
    }
    // Добавить последнюю неиспользованную строку в последовательность
    //  (нужно для обоатного хода)
    for (int i = 0; i < rows; i++) {
        if (!was_pivot[i]) {
            pivot_order[rows - 1] = i;
            break;
        }
    }
    // Обратный ход
    for (int n = rows - 1; n >= 0 ; n--) {
        d = double(0);
        for (int k = n + 1; k < rows; k++)
        {
            d += result[pivot_order[k]] *
                temp_matrix[pivot_order[n] * cols + k];
        }
        result[pivot_order[n]] = (temp_vector[pivot_order[n]] - d) /
            temp_matrix[pivot_order[n] * cols + n];
    }
    if (result[pivot_order[rows - 1]] == 0.0)
    {
        throw("Singular matrix");
    }
    

    return result;
}


Matrix ParallelGauss(const Matrix& matrix, int rows, int cols,
    const Matrix& vec, int vector_size) {
    if ((rows != vector_size) || (rows != cols)) {
        throw("Invalid size");
    }
    int procNum, procRank;
    std::vector<int> col_in_process(cols + 1);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    const int delta = (cols + 1) / procNum;
    const int remain = (cols + 1) % procNum;
    int remain_for_proc = (remain > procRank ? 1 : 0);
    Matrix local_matrix((delta + remain_for_proc) * rows);
    std::vector<double> coefs(rows);
    std::vector<int> pivot_order(rows);
    std::vector<double> result(rows);
    bool *was_pivot = new bool[rows];
    for (int i = 0; i < rows; i++) {
        was_pivot[i] = false;
    }
    std::vector<bool> col_index(delta + remain_for_proc);
    // Создать тип данных - столбец
    int *bloclens = new int[rows * delta];
    int *offsets = new int[rows * delta];
    offsets[0] = 0;
    bloclens[0] = 1;
    for (int i = 1; i < rows * delta; i++) {
        offsets[i] = 0;
        bloclens[i] = 1;
        if (i / delta == 0) {
           offsets[i] += remain;
        }
        offsets[i] += delta + offsets[i - 1];
    }
    MPI_Datatype ColumnRibbonShort;
    MPI_Type_indexed(rows * delta, bloclens, offsets, MPI_DOUBLE, &ColumnRibbonShort);
    MPI_Type_commit(&ColumnRibbonShort);

    delete[] bloclens;
    delete[] offsets;
    if (remain > 0)
    {
        int *bloclens = new int[rows * delta];
        int *offsets = new int[rows * delta];
        offsets[0] = 0;
        bloclens[0] = 1;
        for (int i = 1; i < rows * delta; i++) {
            offsets[i] = 0;
            bloclens[i] = 1;
            if (i / (delta + 1) == 0) {
                offsets[i] -= delta - remain;
            }
            offsets[i] += delta + offsets[i - 1];
        }
        MPI_Datatype ColumnRibbonLong;
        MPI_Type_indexed(rows * delta, bloclens, offsets, MPI_DOUBLE, &ColumnRibbonLong);
        MPI_Type_commit(&ColumnRibbonLong);
        delete[] bloclens;
        delete[] offsets;
    }
    
    for(int col = 0; col < cols; col++) {
            col_in_process[col] = col % procNum;
        }
    col_in_process[cols] = (col_in_process[cols - 1] + 1) % procNum;
    // Передача данных и прием данных
    if(procRank == 0) {
        for (int proc_long = 1; proc_long < remain; proc_long++) {
            MPI_Send(matrix.data() + proc_long, 1, ColumnRibbonLong, proc_long, 0, MPI_COMM_WORLD);
        }
        for (int proc_short = (remain == 0 ? 1 : remain); proc_short < procNum; proc_short++) {
            MPI_Send(matrix.data() + proc_short, 1, ColumnRibbonShort, proc_short, 0, MPI_COMM_WORLD);
        }
        // local_matrix для procRank == 0        
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                local_matrix[row * (delta + remain_for_proc) + col / delta] = matrix[row * cols + col];
            }
        }
        // Создать временный вектор b
        Matrix temp_vector(rows);
        temp_vector = vec;
    } else { // Прием данных (local_matrix транспонирована)
        MPI_Status status;
        MPI_Recv(local_matrix.data(), (delta + remain_for_proc) * rows, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
    }
    // Прямой ход
    for (int current_col = 0; current_col < cols - 1; current_col++) {
        int new_root = 0;
        if (current_col % delta == procRank) {
            new_root = procRank;
            // Найти максимум по модулю в столбце
            double max = 0.0;
            int max_i = 0;
            for (int local_col = 0; local_col < rows; local_col++) {
                if ((fabs(local_matrix[(current_col / delta) * rows + local_col]) >= fabs(max))&&(!was_pivot[i])) {
                    max = local_matrix[(current_col / delta) * rows + local_col];
                    max_i = local_col;
                }
            }
            if (max == 0.0)
            {
                throw("Singular matrix")
            }
            was_pivot[max_i] = true; 
            pivot_order[current_col] = max_i;
            // Подсчитать коэффиценты
            for (int k = 0; k < rows; k++) {
                coefs[k] = double(0);
                if (!was_pivot[k]) {
                    coefs[k] = double(local_matrix[(current_col / delta) * rows + k]) /
                                double(local_matrix[(current_col / delta) * rows + max]);
                }
            }
        }
        // Передать was_pivot, coefs, pivot_order
        MPI_Bcast(was_pivot, rows, MPI_DOUBLE, new_root, MPI_COMM_WORLD);
        MPI_Bcast(coefs.data(), rows, MPI_DOUBLE, new_root, MPI_COMM_WORLD);
        MPI_Bcast(pivot_order.data() + current_col, 1, MPI_INT, new_root, MPI_COMM_WORLD);
        // Вычесть ведущую строку из остальных
        for (int local_row = 0; local_row < delta + remain_for_proc; local_row++) {    
            for (int local_col = 0; local_col < rows; local_col++) {
                if (!was_pivot[local_col]) {
                    local_matrix[local_row* (delta + remain_for_proc) + local_col] -=
                    double(coefs[local_col]) *
                    double(local_matrix[local_row * (delta + remain_for_proc) + pivot_order[current_col]]);
                }
            }
            
        }
        // Повторить для вектора b
        if (procRank == 0) {
            for (int row = 0; row < rows; row++) {   
                if (!was_pivot[row]) {
                    temp_vector[row] -= double(temp_vector[pivot_order[current_col]]) * double(coefs[row]);
                }  
            }
        }
    }
    // Добавить последнюю неиспользованную строку в последовательность
    //  (нужно для обоатного хода)
    for (int i = 0; i < rows; i++) {
        if (!was_pivot[i]) {
            pivot_order[rows - 1] = i;
            break;
        }
    }
    // Обратный ход
    double d;
    int root = 0;
    for (int n = rows - 1; n >= 0 ; n--) {
        if(n / delta == procRank) {
            root = procRank;
            d = double(0);
            for (int k = n + 1; k < rows; k++)
            {
                d += result[pivot_order[k]] *
                    local_matrix[pivot_order[n] * rows + k];
            }
            result[pivot_order[n]] = (temp_vector[pivot_order[n]] - d) /
                temp_matrix[(n / delta) * rows + pivot_order[n]];
            if (result[pivot_order[rows - 1]] == 0.0)
            {
                throw("Singular matrix");
            }
        }
        MPI_Bcast(result.data(), rows, MPI_DOUBLE, root, MPI_COMM_WORLD);
    }
    
    delete[] was_pivot;
    MPI_Type_free(&ColumnRibbonShort);
    MPI_Type_free(&ColumnRibbonLong);
    return result;
    }