// Copyright 2020 Alexandr Solovev
#ifndef MODULES_TASK_2_SOLOVEV_A_SCATTER
#define MODULES_TASK_2_SOLOVEV_A_SCATTER

#include <mpi.h>
#include <string.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <functional>

int My_Scatter(void* send_data, int send_count, MPI_Datatype send_datatype, void* recv_data,
    int recv_count, MPI_Datatype recv_datatype, int root, MPI_Comm communicator);
#endif  //MODULES_TASK_2_SOLOVEV_A_SCATTER

