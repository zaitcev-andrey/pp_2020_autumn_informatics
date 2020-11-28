// Copyright 2020 Gysarova Daria
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <random>
#include <cmath>
#include "./hypercube.h"

TEST(Parallel_Operations_MPI, Test_Trans0to1) {
    MPI_Comm comm;
    int rank, size;
    int in = 22;
    int out;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    comm = HyperCube();
    if (size == 1) {
        out = 22;
    } else {
        if (rank == 0) {
            MPI_Send(&in, 1, MPI_INT, 1, 0, comm);
        }
        if (rank == 1) {
            MPI_Status status;
            MPI_Recv(&out, 1, MPI_INT, 0, 0, comm, &status);
        }
    }
    if (rank == 1) {
        ASSERT_EQ(in, out);
    }
}
TEST(Parallel_Operations_MPI, Test_TransInt) {
    MPI_Comm comm;
    int rank, size;
    int proc1 = 0;
    int proc2 = 0;
    int in = 222;
    int out;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    comm = HyperCube();
    if (size == 1) {
        out = 222;
    } else {
        int d = Dim(size);
        int newsize = pow(2, d);
        std::mt19937 gen;
        std::uniform_int_distribution<> range{ 0, newsize - 1 };
        while (proc1 == proc2) {
            proc1 = range(gen);
            proc2 = range(gen);
        }
        if (rank == proc1) {
            MPI_Send(&in, 1, MPI_INT, proc2, 0, comm);
        }
        if (rank == proc2) {
            MPI_Status status;
            MPI_Recv(&out, 1, MPI_INT, proc1, 0, comm, &status);
        }
    }
    if (rank == proc2) {
        ASSERT_EQ(in, out);
    }
}
TEST(Parallel_Operations_MPI, Test_TransFloat) {
    MPI_Comm comm;
    int rank, size;
    int proc1 = 0;
    int proc2 = 0;
    float in = 22.22;
    float out;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    comm = HyperCube();
    if (size == 1) {
        out = 22.22;
    } else {
        int d = Dim(size);
        int newsize = pow(2, d);
        std::mt19937 gen;
        std::uniform_int_distribution<> range{ 0, newsize - 1 };
        while (proc1 == proc2) {
            proc1 = range(gen);
            proc2 = range(gen);
        }
        if (rank == proc1) {
            MPI_Send(&in, 1, MPI_FLOAT, proc2, 0, comm);
        }
        if (rank == proc2) {
            MPI_Status status;
            MPI_Recv(&out, 1, MPI_FLOAT, proc1, 0, comm, &status);
        }
    }
    if (rank == proc2) {
        ASSERT_EQ(in, out);
    }
}
TEST(Parallel_Operations_MPI, Test_TransDouble) {
    MPI_Comm comm;
    int rank, size;
    int proc1 = 0;
    int proc2 = 0;
    double in = 22.22222222;
    double out;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    comm = HyperCube();
    if (size == 1) {
        out = 22.22222222;
    } else {
        int d = Dim(size);
        int newsize = pow(2, d);
        std::mt19937 gen;
        std::uniform_int_distribution<> range{ 0, newsize - 1 };
        while (proc1 == proc2) {
            proc1 = range(gen);
            proc2 = range(gen);
        }
        if (rank == proc1) {
            MPI_Send(&in, 1, MPI_DOUBLE, proc2, 0, comm);
        }
        if (rank == proc2) {
            MPI_Status status;
            MPI_Recv(&out, 1, MPI_DOUBLE, proc1, 0, comm, &status);
        }
    }
    if (rank == proc2) {
        ASSERT_EQ(in, out);
    }
}
TEST(Parallel_Operations_MPI, Test_TransChar) {
    MPI_Comm comm;
    int rank, size;
    int proc1 = 0;
    int proc2 = 0;
    char in = 2;
    char out;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    comm = HyperCube();
    if (size == 1) {
        out = 2;
    } else {
        int d = Dim(size);
        int newsize = pow(2, d);
        std::mt19937 gen;
        std::uniform_int_distribution<> range{ 0, newsize - 1 };
        while (proc1 == proc2) {
            proc1 = range(gen);
            proc2 = range(gen);
        }
        if (rank == proc1) {
            MPI_Send(&in, 1, MPI_CHAR, proc2, 0, comm);
        }
        if (rank == proc2) {
            MPI_Status status;
            MPI_Recv(&out, 1, MPI_CHAR, proc1, 0, comm, &status);
        }
    }
    if (rank == proc2) {
        ASSERT_EQ(in, out);
    }
}
int main(int argc, char**argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
