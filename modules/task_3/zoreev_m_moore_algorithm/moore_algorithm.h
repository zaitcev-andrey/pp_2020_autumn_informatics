// Copyright 2020 Zoreev Mikhail
#ifndef MODULES_TASK_3_ZOREEV_M_MOORE_ALGORITHM_MOORE_ALGORITHM_H_
#define MODULES_TASK_3_ZOREEV_M_MOORE_ALGORITHM_MOORE_ALGORITHM_H_

#include <mpi.h>

#include <stdexcept>

size_t* mooreAlgorithm(size_t vertices_count, size_t edges_count, int64_t *edges, size_t root);

#endif // MODULES_TASK_3_ZOREEV_M_MOORE_ALGORITHM_MOORE_ALGORITHM_H_