// Copyright 2020 Molotkova Svetlana
#ifndef MODULES_TASK_1_MOLOTKOVA_S_MAX_IN_ROWS_H
#define MODULES_TASK_1_MOLOTKOVA_S_MAX_IN_ROWS_H

#include "mpi.h"
#include <cmath>
#include <ctime>
#include <iomanip>
#include <math.h>
#include <map>
#include <vector>

double findmax(int stolbnum, double** arr, int N);
int malloc2d(double*** array, int n, int m);
int free2d(double*** array);
std::vector<double> Get_max_parallel(double** matrix, int stolb, int stroka);
std::vector<double> Get_max_sequestional(double** matrix, int stolb, int stroka);
double** Matrix(int stolb, int stroka);

#endif  // MODULES_TASK_1_MOLOTKOVA_S_MAX_IN_ROWS_H
