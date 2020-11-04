// Copyright 2020 Gogov Vladislav
#include <mpi.h>
#include <iostream>
#include <vector>
#include <random>
#include "../../../modules/task_2/gogov_v_block_striped_columnwise/block_striped_columnwise.h"

void printVector(std::vector<int>& vec, int vecSize) {
    std::cout << "Vector print:" << std::endl;
    for(int i = 0; i < vecSize; i++)
        std::cout << vec[i] << std::endl;
}

void printMatrix(std::vector<int>& vec, int rows, int cols) {
    std::cout << "Matrix print:" << std::endl;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            std::cout << vec[i * cols + j] << "  ";
        }
        std::cout << std::endl;
    }
}

Matrix createRandomMatrix(int rows, int cols) {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    Matrix matrix(rows * cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i * cols + j] = static_cast<int>(mersenne() % 100u);
        }
    }
    return matrix;
}

std::vector<int> multMatrixByVectorSequential(const Matrix& matrix, int rows, int cols, const std::vector<int>& vec, int vecSize) {
    if (cols != vecSize) {
        throw("Invalid size");
    }
    std::vector<int> result(rows, 0);
    for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            result[i] += matrix[i * cols + j] * vec[j];
        }
    }
    return result;
}

void arraysDistribution(std::vector<int>& sendNum, std::vector<int>& sendInd, int n, int procNum, int remain, int cols) {
    sendNum[0] = (remain != 0 ? n + 1 : n);
    sendInd[0] = 0;
    for (int i = 1; i < procNum; i++) {
        sendNum[i] = (i < remain ? n + 1 : n);
        sendInd[i] = sendInd[i - 1] + sendNum[i - 1];
    }
}

std::vector<int> sumMatrixByRows(const std::vector<int>& vec, int rows, int cols) {
    std::vector<int> result(cols, 0);
    for (int i = 0; i < cols; i++) {
        int temp = 0;
        for (int j = 0; j < rows; j++) {
            temp += vec[j * cols + i];
        }
        result[i] = temp;
    }
    return result;
}

std::vector<int> multMatrixByVectorParallel(const Matrix& matrix, int rows, int cols, std::vector<int>& vec, int vecSize) {
    if (cols != vecSize) {
        throw("Invalid size");
    }
    int procNum, procRank;
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int n = cols / procNum;
    int remain = cols - n * procNum;

    //  Определение массивов для type
    std::vector<int> sendNum(procNum);
    std::vector<int> sendInd(procNum);
    arraysDistribution(sendNum, sendInd, n, procNum, remain, cols);

    //  Определение производного типа столбец
    int countType = (remain == 0 ? 1 : 2);
    MPI_Datatype* colType = new MPI_Datatype[countType];
    for (int i = 0; i < countType; i++) {
        MPI_Type_vector(rows, sendNum[i == 0 ? i : procNum - 1], cols, MPI_INT, &colType[i]);
        MPI_Type_commit(&colType[i]);
    }

    //  Отправка вектора
    std::vector<int> partVector(sendNum[procRank]);
    MPI_Scatterv(vec.data(), sendNum.data(), sendInd.data(), MPI_INT, 
                partVector.data(), sendNum[procRank], MPI_INT, 0, MPI_COMM_WORLD);

    //  Передача и прием матрицы
    std::vector<int> colVector(sendNum[procRank] * rows);
    if (procRank == 0) {
        for (int i = 1; i < procNum; i++) {
            MPI_Send(matrix.data() + sendInd[i], 1, colType[remain == 0 || i < remain ? 0 : 1], i, 0, MPI_COMM_WORLD);
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < sendNum[procRank]; j++) {
                colVector[i * sendNum[procRank] + j] = matrix[i * cols + j];
            }
        }
    } else {
        MPI_Status status;
        MPI_Recv(colVector.data(), sendNum[procRank] * rows, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }
    std::vector<int> localVector = multMatrixByVectorSequential(colVector, rows, sendNum[procRank], 
                                                                partVector, sendNum[procRank]);

    //  Сбор промежуточных векторов
    std::vector<int> tempMatrix(procNum * rows);
    MPI_Gather(localVector.data(), static_cast<int>(localVector.size()), MPI_INT, 
                tempMatrix.data(), rows, MPI_INT, 0, MPI_COMM_WORLD);
    
    // Суммирование столбцов
    std::vector<int> resultVector(0);
    if (procRank == 0) {
        resultVector = sumMatrixByRows(tempMatrix, procNum, rows);
    }

    for (int i = 0; i < countType; i++) 
        MPI_Type_free(&colType[i]);
    return resultVector;
}