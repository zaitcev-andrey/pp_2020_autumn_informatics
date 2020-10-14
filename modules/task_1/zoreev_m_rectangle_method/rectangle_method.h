// Copyright 2020 Zoreev Mikhail
#ifndef MODULES_TASK_1_ZOREEV_M_RECTANGLE_METHOD_H_
#define MODULES_TASK_1_ZOREEV_M_RECTANGLE_METHOD_H_

#include <mpi.h>

double Integralseqential(double (*funсtion)(double),double a, double b, size_t count);

double Integralparallel(double (*funсtion)(double),double a, double b, size_t count);

#endif // MODULES_TASK_1_ZOREEV_M_RECTANGLE_METHOD_H_
