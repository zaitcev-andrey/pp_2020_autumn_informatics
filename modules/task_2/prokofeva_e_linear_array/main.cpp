// Copyright 2020 Prokofeva Elizaveta
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include "./linear_array.h"

TEST(Lin_Topology_MPI, test_graph) {
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size == 1) {
        ASSERT_EQ(true, true);
        return;
    }

    MPI_Comm communicator = create_comm(MPI_COMM_WORLD);

    int nodes, edges;
    MPI_Graphdims_get(communicator, &nodes, &edges);
    ASSERT_EQ(nodes, size);
    ASSERT_EQ(edges, 2 * (size - 1));
}

TEST(Lin_Topology_MPI, test_graph_neighbors) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size == 1) {
        ASSERT_EQ(true, true);
        return;
    }
    MPI_Comm communicator = create_comm(MPI_COMM_WORLD);
    MPI_Comm_rank(communicator, &rank);
    int count_neighbors;
    if ((rank == 0) || (rank == size - 1)) {
        MPI_Graph_neighbors_count(communicator, rank, &count_neighbors);
        ASSERT_EQ(count_neighbors, 1);
    } else {
        MPI_Graph_neighbors_count(communicator, rank, &count_neighbors);
        ASSERT_EQ(count_neighbors, 2);
    }
}

TEST(Lin_Topology_MPI, test_send_recv_from_first_to_last) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size == 1) {
        ASSERT_EQ(true, true);
        return;
    }

    MPI_Comm communicator = create_comm(MPI_COMM_WORLD);
    MPI_Comm_rank(communicator, &rank);

    int rank_s = 0;
    int rank_r = size - 1;

    int size_vec = 10;
    int* message = new int[size_vec];
    message = getRandomVector(size_vec);

    int* result_message = send_recv(message, size_vec, MPI_INT, rank_r, 0, communicator, rank_s, rank);
    if (rank == rank_r) {
        for (int i = 0; i < size_vec; i++) {
            ASSERT_EQ(message[i], result_message[i]);
        }
    }
}

TEST(Lin_Topology_MPI, test_send_recv_from_first_to_last_big_size) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size == 1) {
        ASSERT_EQ(true, true);
        return;
    }

    MPI_Comm communicator = create_comm(MPI_COMM_WORLD);
    MPI_Comm_rank(communicator, &rank);

    int rank_s = 0;
    int rank_r = size - 1;

    int size_vec = 100000;
    int* message = new int[size_vec];
    message = getRandomVector(size_vec);

    int* result_message = send_recv(message, size_vec, MPI_INT, rank_r, 0, communicator, rank_s, rank);
    if (rank == rank_r) {
        for (int i = 0; i < size_vec; i++) {
            ASSERT_EQ(message[i], result_message[i]);
        }
    }
}

TEST(Lin_Topology_MPI, test_send_recv_from_last_to_first) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size == 1) {
        ASSERT_EQ(true, true);
        return;
    }

    MPI_Comm communicator = create_comm(MPI_COMM_WORLD);
    MPI_Comm_rank(communicator, &rank);

    int rank_s = size - 1;
    int rank_r = 0;

    int size_vec = 10;
    int* message = new int[size_vec];
    message = getRandomVector(size_vec);

    int* result_message = send_recv(message, size_vec, MPI_INT, rank_r, 0, communicator, rank_s, rank);
    if (rank == rank_r) {
        for (int i = 0; i < size_vec; i++) {
            ASSERT_EQ(message[i], result_message[i]);
        }
    }
}

TEST(Lin_Topology_MPI, test_send_recv_from_last_to_first_big_size) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size == 1) {
        ASSERT_EQ(true, true);
        return;
    }

    MPI_Comm communicator = create_comm(MPI_COMM_WORLD);
    MPI_Comm_rank(communicator, &rank);

    int rank_s = size - 1;
    int rank_r = 0;

    int size_vec = 100000;
    int* message = new int[size_vec];
    message = getRandomVector(size_vec);

    int* result_message = send_recv(message, size_vec, MPI_INT, rank_r, 0, communicator, rank_s, rank);
    if (rank == rank_r) {
        for (int i = 0; i < size_vec; i++) {
                ASSERT_EQ(message[i], result_message[i]);
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
