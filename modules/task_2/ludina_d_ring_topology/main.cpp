// Copyright 2020 Ludina Daria
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include "./ring_topology.h"

TEST(Topology_Ring, Create_Ring_Topology) {
  MPI_Comm ringcomm = createRingcomm(MPI_COMM_WORLD);

  ASSERT_TRUE(ringcomm != MPI_COMM_NULL);
}

TEST(Topology_Ring, Test_Send_Array) {
  MPI_Comm ringcomm = createRingcomm(MPI_COMM_WORLD);
  int rank, size;
  MPI_Comm_size(ringcomm, &size);
  MPI_Comm_rank(ringcomm, &rank);

  int size_ar = 5;
  int rank_source = 1;
  int rank_dest = 3;

  int* arr = new int[size_ar] { 1, 4, 9, 3, 5 };

  int* arr2 = Send(arr, size_ar, rank_source, rank_dest, ringcomm);
  if (rank == rank_dest) {
    for (int i = 0; i < size_ar; i++) {
      ASSERT_EQ(arr[i], arr2[i]);
    }
  }
}

TEST(Topology_Ring, Test_Send_Source_less_Dest) {
  MPI_Comm ringcomm = createRingcomm(MPI_COMM_WORLD);
  int rank, size;
  MPI_Comm_size(ringcomm, &size);
  MPI_Comm_rank(ringcomm, &rank);

  int size_ar = 7;
  int rank_source = 1;
  int rank_dest = size - 1;

  int* arr = new int[size_ar];
  arr = createRandomArray(size_ar);

  int* arr2 = Send(arr, size_ar, rank_source, rank_dest, ringcomm);
  if (rank == rank_dest) {
    for (int i = 0; i < size_ar; i++) {
      ASSERT_EQ(arr[i], arr2[i]);
    }
  }
}

TEST(Topology_Ring, Test_Send_Source_more_Dest) {
  MPI_Comm ringcomm = createRingcomm(MPI_COMM_WORLD);
  int rank, size;
  MPI_Comm_size(ringcomm, &size);
  MPI_Comm_rank(ringcomm, &rank);
  int size_ar = 15;
  int rank_source = size - 1;
  int rank_dest = 0;

  int* arr = new int[size_ar];
  arr = createRandomArray(size_ar);

  int* arr2 = Send(arr, size_ar, rank_source, rank_dest, ringcomm);
  if (rank == rank_dest) {
    for (int i = 0; i < size_ar; i++) {
      ASSERT_EQ(arr[i], arr2[i]);
    }
  }
}

TEST(Topology_Ring, Test_Send_Source_equal_Dest) {
  MPI_Comm ringcomm = createRingcomm(MPI_COMM_WORLD);
  int rank, size;
  MPI_Comm_size(ringcomm, &size);
  MPI_Comm_rank(ringcomm, &rank);
  int size_ar = 40;
  int rank_source = 1;
  int rank_dest = 1;

  int* arr = new int[size_ar];
  arr = createRandomArray(size_ar);

  int* arr2 = Send(arr, size_ar, rank_source, rank_dest, ringcomm);
  if (rank == rank_dest) {
    for (int i = 0; i < size_ar; i++) {
      ASSERT_EQ(arr[i], arr2[i]);
    }
  }
}

TEST(Topology_Ring, Test_Send_Big_Array) {
  MPI_Comm ringcomm = createRingcomm(MPI_COMM_WORLD);
  int rank, size;
  MPI_Comm_size(ringcomm, &size);
  MPI_Comm_rank(ringcomm, &rank);
  int size_ar = 2000;
  int rank_source = 0;
  int rank_dest = size - 1;

  int* arr = new int[size_ar];
  arr = createRandomArray(size_ar);

  int* arr2 = Send(arr, size_ar, rank_source, rank_dest, ringcomm);
  if (rank == rank_dest) {
    for (int i = 0; i < size_ar; i++) {
      ASSERT_EQ(arr[i], arr2[i]);
    }
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  MPI_Init(&argc, &argv);

  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners& listeners =
    ::testing::UnitTest::GetInstance()->listeners();

  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());

  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}
