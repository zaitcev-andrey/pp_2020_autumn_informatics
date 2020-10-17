#ifndef MODULES_TASK_1_TKACHEV_A_MATRIX_COLUMNS_SUM_MATRIX_COLUMNS_SUM_H_
#define MODULES_TASK_1_TKACHEV_A_MATRIX_COLUMNS_SUM_MATRIX_COLUMNS_SUM_H_
#include <vector>

std::vector<int8_t> generateRandomMatrix(uint8_t count_rows, uint8_t count_columns = 0);
int16_t getSequentialColsSum(std::vector<int8_t> matrix, uint8_t count_columns = 0);
int16_t getParallelColsSum(std::vector<int8_t> matrix, uint8_t count_columns, int count_processes);

#endif  // MODULES_TASK_1_TKACHEV_A_MATRIX_COLUMNS_SUM_MATRIX_COLUMNS_SUM_H_
