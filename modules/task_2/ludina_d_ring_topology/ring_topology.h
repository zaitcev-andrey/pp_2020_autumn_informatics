// Copyright 2020 Ludina Daria
#ifndef MODULES_TASK_2_LUDINA_D_RING_TOPOLOGY_RING_TOPOLOGY_H_
#define MODULES_TASK_2_LUDINA_D_RING_TOPOLOGY_RING_TOPOLOGY_H_

#include <mpi.h>
#include <random>
#include <ctime>

MPI_Comm createRingcomm(MPI_Comm oldComm);
int* createRandomArray(int size);
int* Send(int* vec, int size_v, int rank_source, int rank_dest, MPI_Comm ringComm);

#endif  // MODULES_TASK_2_LUDINA_D_RING_TOPOLOGY_RING_TOPOLOGY_H_
