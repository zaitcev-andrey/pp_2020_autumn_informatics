// Copyright 2020 Gogov Vladislav
#ifndef MODULES_TASK_3_GOGOV_V_ALGORITHM_FOX_ALGORITHM_FOX_H_
#define MODULES_TASK_3_GOGOV_V_ALGORITHM_FOX_ALGORITHM_FOX_H_
#include <vector>

using Matrix = std::vector<double>;

struct Grid {  // Решетка
    int dimGrid;  // Порядок решетки
    int numRow;  // Номер строки
    int numCol;  // Номер стобца
    MPI_Comm commGrid;  // Коммуникатор решетки
    MPI_Comm commRow;  // Коммуникатор строки
    MPI_Comm commCols;  // Коммуникатор столбца
};

bool assertMatrix(const Matrix& matrixA, const Matrix& matrixB);
bool checkSize(int* size);

void printMatrix(const Matrix& matrix, int size);
Matrix createRandomMatrix(int size);

void createGrid(Grid* grid);  // Создание решетки

Matrix MultiplyMatrixSequential(const Matrix& matrixA, const Matrix& matrixB, int size);
Matrix MultiplyMatrixParallel(const Matrix& matrixA, const Matrix& matrixB, int size);

#endif  // MODULES_TASK_3_GOGOV_V_ALGORITHM_FOX_ALGORITHM_FOX_H_
