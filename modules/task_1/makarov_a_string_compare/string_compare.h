// Copyright 2020 Makarov Alexander
#ifndef MODULES_TASK_1_MAKAROV_A_STR_SUM_OPS_MPI_H_
#define MODULES_TASK_1_MAKAROV_A_STR_SUM_OPS_MPI_H_

#include <string>

std::string getRandomString(int sz);
int compareParallel(std::string global_str,
                          int count_chars);
int compareSequential(std::string str);

#endif  // MODULES_TASK_1_MAKAROV_A_STR_SUM_OPS_MPI_H_
