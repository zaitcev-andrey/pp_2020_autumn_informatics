// Copyright 2020 Hassan EzzAldeen
#ifndef MODULES_TASK_2_HASSAN_EZZALDEEN_SCATTTER_H_
#define MODULES_TASK_2_HASSAN_EZZALDEEN_SCATTTER_H_
#include <mpi.h>
#include <string>
#include <cstring>
#include <vector>

int MPI_Scatter_custom(void* sendBuf, int sendCount,
    MPI_Datatype sendType, void* recvBuf,
    int recvCount, MPI_Datatype recvType,
    int ROOT, MPI_Comm COMM);

#endif  // MODULES_TASK_2_HASSAN_EZZALDEEN_SCATTTER_H_
