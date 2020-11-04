// Copyright 2020 Gogov Vladislav
#ifndef MODULES_TASK_2_GOGOV_V_BLOCK_STRIPED_COLUMNWISE_BLOCK_STRIPED_COLUMNWISE_H_
#define MODULES_TASK_2_GOGOV_V_BLOCK_STRIPED_COLUMNWISE_BLOCK_STRIPED_COLUMNWISE_H_
#include <vector>

using Matrix = std::vector<int>;

void printVector(const std::vector<int>& vec, int vecSize);
void printMatrix(const std::vector<int>& vec, int rows, int cols);
Matrix createRandomMatrix(int rows, int cols);

void arraysDistribution(int* sendNum, int* sendInd, int n, int procNum, int remain, int cols);
std::vector<int> sumMatrixByRows(const std::vector<int>& vec, int rows, int cols);

std::vector<int> multMatrixByVectorSequential(const Matrix& matirx, int rows, int cols,
                                            const std::vector<int>& vec, int vecSize);
std::vector<int> multMatrixByVectorParallel(const Matrix& matirx, int rows, int cols,
                                            const std::vector<int>& vec, int vecSize);

#endif  // MODULES_TASK_2_GOGOV_V_BLOCK_STRIPED_COLUMNWISE_BLOCK_STRIPED_COLUMNWISE_H_
