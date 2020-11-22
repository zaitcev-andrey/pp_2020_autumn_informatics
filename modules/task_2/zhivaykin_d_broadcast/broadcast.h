// Copyright 2020 Zhivaykin Daniil
#include <mpi.h>
#include <stdexcept>
#ifndef MODULES_TASK_1_ZHIVAYKIN_D_RECTANGLE_METHOD_RECTANGLE_H_
#define MODULES_TASK_1_ZHIVAYKIN_D_RECTANGLE_METHOD_RECTANGLE_H_

void myBcast(void *buf, int count, MPI_Datatype type, int root, MPI_Comm comm);

#endif  // MODULES_TASK_1_ZHIVAYKIN_D_RECTANGLE_METHOD_RECTANGLE_H_
