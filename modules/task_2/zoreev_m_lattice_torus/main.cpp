// Copyright 2020 Zoreev Mikhail

#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <mpi.h>

#include "../../../modules/task_2/zoreev_m_lattice_torus/lattice_torus.h"

TEST(Lattice_Torus_MPI, Lattice_Torus_Is_Cart) {
    int status = MPI_UNDEFINED;
    MPI_Comm communicator = createLatticeTorus(MPI_COMM_WORLD, 2);
    MPI_Topo_test(communicator, &status);

    ASSERT_EQ(status, MPI_CART);
}

TEST(Lattice_Torus_MPI, Lattice_Torus_Has_Right_Parameters) {
    int dimensions_count;
    int coordinates[2], dimensions[2], periods[2];
    MPI_Comm communicator = createLatticeTorus(MPI_COMM_WORLD, 2);
    MPI_Cartdim_get(communicator, &dimensions_count);
    MPI_Cart_get(communicator, dimensions_count, dimensions, periods, coordinates);

    ASSERT_EQ(dimensions_count, 2);
    EXPECT_TRUE(periods[0] & periods[1]);
}

TEST(Lattice_Torus_MPI, Lattice_Torus_Send_Recv) {
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size == 1) {
        ASSERT_EQ(true, true);
        return;
    }

    MPI_Comm communicator = createLatticeTorus(MPI_COMM_WORLD, 2);
    int rank;
    int coordinates[2], dimensions[2], periods[2];
    MPI_Comm_rank(communicator, &rank);
    MPI_Cart_coords(communicator, rank, 2, coordinates);
    MPI_Cart_get(communicator, 2, dimensions, periods, coordinates);

    int out_messange = 5, in_messange = 0;
    if ((coordinates[0] == 0) && (coordinates[1] == 0)) {
        int dest_coordinates[] = {dimensions[0] - 1, dimensions[1] - 1};
        LatticeTorusSend(&out_messange, 1, MPI_INT, dest_coordinates, 0, communicator);
    } else if ((coordinates[0] == dimensions[0] - 1) && (coordinates[1] == dimensions[1] - 1)) {
        MPI_Status status;
        int source_coordinates[] = {0, 0};
        LatticeTorusRecv(&in_messange, 1, MPI_INT, source_coordinates, 0, communicator, &status);
        ASSERT_EQ(in_messange, out_messange);
    }
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners &listeners = ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
