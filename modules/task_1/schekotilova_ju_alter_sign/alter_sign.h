// Copyright 2020 Schekotilova Julia
#ifndef MODULES_TASK_1_SCHEKOTILOVA_JU_ALTER_SIGN_MPI_H_
#define MODULES_TASK_1_SCHEKOTILOVA_JU_ALTER_SIGN_MPI_H_

#include <vector>
#include <string>
#include <iostream>
#include <mpi.h>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

vector<int> getRandomVector(int  sz);
int getParallelOperations(vector<int> vec, int count_size_vec);
int getSequentialOperations(vector<int> v, int size_v);

#endif  // MODULES_TASK_1_SCHEKOTILOVA_JU_ALTER_SIGN_MPI_H_
