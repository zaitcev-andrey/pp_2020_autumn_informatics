// Copyright 2020 Ludina Daria
#include "../../../modules/task_2/ludina_d_ring_topology/ring_topology.h"

MPI_Comm createRingcomm(MPI_Comm oldComm) {
  int ndims = 1;

  int* dims = new int[ndims];
  int* periods = new int[ndims];

  periods[0] = 1;

  MPI_Comm_size(oldComm, &dims[0]);

  int reorder = 0;

  MPI_Comm ringComm;
  MPI_Cart_create(oldComm, ndims, dims, periods, reorder, &ringComm);
  return ringComm;
}

int* createRandomArray(int size) {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  int* array = new int[size];
  for (int i = 0; i < size; i++) {
    array[i] = gen() % 100;
  }
  return array;
}

int* Send(int* arr_1, int size_arr, int rank_source, int rank_dest, MPI_Comm ringComm) {
  int size, rank;
  MPI_Comm_size(ringComm, &size);
  MPI_Comm_rank(ringComm, &rank);

  int* res = new int[size_arr];

  if (rank_source == rank_dest)
    return arr_1;

  int curr_rank_source, curr_rank_dest;
  MPI_Status status;
  MPI_Cart_shift(ringComm, 0, 1, &curr_rank_source, &curr_rank_dest);
  if (rank == rank_source) {
    MPI_Send(&arr_1[0], size_arr, MPI_INT, curr_rank_dest, 0, ringComm);
  } else if (rank == rank_dest) {
    MPI_Recv(&res[0], size_arr, MPI_INT, curr_rank_source, 0, ringComm, &status);
  } else if (rank_source < rank_dest && rank > rank_source && rank < rank_dest) {
    MPI_Recv(&res[0], size_arr, MPI_INT, curr_rank_source, 0, ringComm, &status);
    MPI_Send(&arr_1[0], size_arr, MPI_INT, curr_rank_dest, 0, ringComm);
  } else if (rank_source > rank_dest && ((rank > rank_source && rank < size) || (rank < rank_dest))) {
    MPI_Recv(&res[0], size_arr, MPI_INT, curr_rank_source, 0, ringComm, &status);
    MPI_Send(&arr_1[0], size_arr, MPI_INT, curr_rank_dest, 0, ringComm);
  }
  return res;
}
