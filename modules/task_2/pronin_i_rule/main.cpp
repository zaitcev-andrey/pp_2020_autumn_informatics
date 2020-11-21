// Copyright 2020 Pronin Igor
#include <mpi.h>
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <ctime>
#include <random>
#include "./rule.h"

TEST(Parallel_Operations_MPI, Build) {
    int status = MPI_UNDEFINED;
    MPI_Comm communicator = createRuleComm(MPI_COMM_WORLD, 10);
    MPI_Topo_test(communicator, &status);
    ASSERT_EQ(status, MPI_CART);
}
TEST(Parallel_Operations_MPI, Ndims_Periods_Coordinates) {
    int ndims;
    int dims[1];
    int periods[1];
    int coordinates[1];
    MPI_Comm communicator = createRuleComm(MPI_COMM_WORLD, 10);
    MPI_Cartdim_get(communicator, &ndims);
    MPI_Cart_get(communicator, 1, dims, periods, coordinates);
    ASSERT_EQ(ndims, 1);
    ASSERT_EQ(periods[0], 0);
}
TEST(Parallel_Operations_MPI, Ferst_To_Last) {
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size == 1) {
        ASSERT_EQ(true, true);
        return;
    }
    int dims[1];
    int periods[1];
    int coordinates[1];
    int send_message = 5;
    int recive_message = 0;
    MPI_Comm communicator = createRuleComm(MPI_COMM_WORLD, 10);
    MPI_Cart_get(communicator, 1, dims, periods, coordinates);
    if (coordinates[0] == 0) {
        int rank_recive;
        int dest_coordinates[] = { dims[0] - 1 };
        MPI_Cart_rank(communicator, dest_coordinates, &rank_recive);
        MPI_Send(&send_message, 1, MPI_INT, rank_recive, 0, communicator);
    } else if (coordinates[0] == dims[0] - 1) {
        MPI_Status status;
        int rank_send;
        int recive_coordinates[] = { 0 };
        MPI_Cart_rank(communicator, recive_coordinates, &rank_send);
        MPI_Recv(&recive_message, 1, MPI_INT, rank_send, 0, communicator, &status);
        ASSERT_EQ(send_message, recive_message);
    }
}
TEST(Parallel_Operations_MPI, Random_To_Random) {
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size == 1) {
        ASSERT_EQ(true, true);
        return;
    }
    int rank;
    MPI_Comm communicator = createRuleComm(MPI_COMM_WORLD, 10);
    int send_rank;
    int recive_rank;
    int send_message = 5;
    int recive_message = 0;
    std::mt19937 generator;
    generator.seed(static_cast<unsigned int>(time(0)));
    MPI_Comm_rank(communicator, &rank);
    send_rank = generator() % size;
    do {
        recive_rank = generator() % size;
    } while (send_rank == recive_rank);
    if (rank == send_rank) {
        MPI_Send(&send_message, 1, MPI_INT, recive_rank, 0, communicator);
    } else if (rank == recive_rank) {
        MPI_Status status;
        MPI_Recv(&recive_message, 1, MPI_INT, send_rank, 0, communicator, &status);
        ASSERT_EQ(send_message, recive_message);
    }
}
TEST(Parallel_Operations_MPI, Random_To_Next) {
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size == 1) {
        ASSERT_EQ(true, true);
        return;
    }
    int size_rule;
    int rank;
    int rank_random;
    int send_message = 5;
    int recive_message = 0;
    int dims[1];
    int periods[1];
    int coordinates[1];
    std::mt19937 generator;
    generator.seed(static_cast<unsigned int>(time(0)));
    MPI_Comm communicator = createRuleComm(MPI_COMM_WORLD, 10);
    MPI_Comm_size(communicator, &size_rule);
    MPI_Comm_rank(communicator, &rank);
    rank_random = generator() % size_rule;
    int new_rank;
    int super_new_rank;
    if (rank == rank_random) {
        MPI_Cart_get(communicator, 1, dims, periods, coordinates);
        if (coordinates[0] == dims[0]) {
            int new_coordinates[] = { coordinates[0] - 1 };
            MPI_Cart_rank(communicator, new_coordinates, &new_rank);
            MPI_Send(&send_message, 1, MPI_INT, new_rank, 0, communicator);
        } else {
            int super_new_coordinates[] = { coordinates[0] + 1 };
            MPI_Cart_rank(communicator, super_new_coordinates, &super_new_rank);
            MPI_Send(&send_message, 1, MPI_INT, super_new_rank, 0, communicator);
        }
    } else if (rank == new_rank || rank == super_new_rank) {
        MPI_Status status;
        MPI_Recv(&recive_message, 1, MPI_INT, rank_random, 0, communicator, &status);
        ASSERT_EQ(send_message, recive_message);
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
