// Copyright 2020 Bessolitsyn Sergey
#ifndef MODULES_TASK_1_BESSOLITSYN_S_COUNT_SENT_COUNT_SENT_H_
#define MODULES_TASK_1_BESSOLITSYN_S_COUNT_SENT_COUNT_SENT_H_

#include <vector>

std::vector<char> getRandomString(int n);
int getSequentialOperations(std::vector<char> vec, int n);
int getParallelOperations(std::vector<char> global_vec, int count_size_vector);

#endif  // MODULES_TASK_1_BESSOLITSYN_S_COUNT_SENT_COUNT_SENT_H_
