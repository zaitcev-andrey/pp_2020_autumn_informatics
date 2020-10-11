
#ifndef MODULES_TASK_1_NESTEROV_A_VECTOR_SUM_OPS_MPI_H_
#define MODULES_TASK_1_NESTEROV_A_VECTOR_SUM_OPS_MPI_H_

#include <vector>
#include <string>

std::vector<char> getRandomLine(int  size);
int getParallelOperations(std::vector<char> global_vec, int count_size_vector);
int getSequentialOperations(std::vector<char> vec);

#endif  