// Copyright 2020 Gruzdeva Diana
#ifndef MODULES_TASK_1_GRUZDEVA_D_TRAPEZOIDAL_INTEGRAL_TRAPEZOIDAL_INTEGRAL_H_
#define MODULES_TASK_1_GRUZDEVA_D_TRAPEZOIDAL_INTEGRAL_TRAPEZOIDAL_INTEGRAL_H_

#include <mpi.h>
#include <cmath>
#include <functional>

double trap_integral(double a, double b, int n, std::function<double(double)> function);
double trap_integral_parallel(double a, double b, int n, std::function<double(double)> function);

double call_function(std::function<double(double)> function, double value);
double func1(double x);
double func2(double x);
double func3(double x);
double func4(double x);
double func5(double x);

#endif  MODULES_TASK_1_GRUZDEVA_D_TRAPEZOIDAL_INTEGRAL_TRAPEZOIDAL_INTEGRAL_H_