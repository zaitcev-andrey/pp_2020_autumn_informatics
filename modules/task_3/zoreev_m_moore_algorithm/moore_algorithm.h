// Copyright 2020 Zoreev Mikhail
#ifndef MODULES_TASK_3_ZOREEV_M_MOORE_ALGORITHM_MOORE_ALGORITHM_H_
#define MODULES_TASK_3_ZOREEV_M_MOORE_ALGORITHM_MOORE_ALGORITHM_H_

#include <mpi.h>

#include <iostream>
#include <iomanip>
#include <ctime>
#include <random>
#include <stdexcept>

void randomCompleteGraph(size_t size, int64_t *graph);

void printGraph(size_t size, int64_t *graph);
void printPredecessor(size_t size, size_t *predecessor);

size_t *mooreAlgorithm(size_t size, int64_t *graph, size_t root);

#endif // MODULES_TASK_3_ZOREEV_M_MOORE_ALGORITHM_MOORE_ALGORITHM_H_