// Copyright 2020 Kiseleva Anastasia
#include <mpi.h>
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <limits>
#include <iostream>
#include "./zhordan_gauss.h"

const double EPSILON = std::numeric_limits<double>::epsilon()*100000;

TEST(Parallel_MPI, TEST_2x3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int str = 2;
    double array[6]= { 5, 5 , -5, 7, -3, 10 };
    double *res = new double[2];
    double t0, t1;
    t0 = MPI_Wtime();
    res = zhordan_gauss(array, str);
    t1 = MPI_Wtime();
    if (rank == 0) {
        bool check = Check(array, 2, res, EPSILON);
        ASSERT_TRUE(check);
        std::cout << "paralel_time: " << t1 - t0 << std::endl;
        t0 = MPI_Wtime();
        posled(array, 2);
        t1 = MPI_Wtime();
        std::cout << "posled_time: " << t1 - t0 << std::endl;
    }
}

TEST(Parallel_MPI, TEST_3x4) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int str = 3;
    double array[12] = { 3, -9, 15, 15, 5, 8, -10, 2 , 8, -20, 12, -3 };
    double *res = new double[3];
    double t0, t1;
    t0 = MPI_Wtime();
    res = zhordan_gauss(array, str);
    t1 = MPI_Wtime();
    if (rank == 0) {
        bool check = Check(array, 3, res, EPSILON);
        ASSERT_TRUE(check);
        std::cout << "paralel_time: " << t1 - t0 << std::endl;
        t0 = MPI_Wtime();
        posled(array, 3);
        t1 = MPI_Wtime();
        std::cout << "posled_time: " << t1 - t0 << std::endl;
    }
}

TEST(Parallel_MPI, TEST_3x4_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int str = 3;
    double array[12] = { 5, 3, -4, 4, 10, -10 , 1, 1, -3, 5, 2, 4 };
    double *res = new double[3];
    double t0, t1;
    t0 = MPI_Wtime();
    res = zhordan_gauss(array, str);
    t1 = MPI_Wtime();
    if (rank == 0) {
        bool check = Check(array, 3, res, EPSILON);
        ASSERT_TRUE(check);
        std::cout << "paralel_time: " << t1 - t0 << std::endl;
        t0 = MPI_Wtime();
        posled(array, 3);
        t1 = MPI_Wtime();
        std::cout << "posled_time: " << t1 - t0 << std::endl;
    }
}

TEST(Parallel_MPI, TEST_2x3__) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int str = 2;
    double array[6] = { 10, 10 , -10, 12, -8, 15 };
    double *res = new double[2];
    double t0, t1;
    t0 = MPI_Wtime();
    res = zhordan_gauss(array, str);
    t1 = MPI_Wtime();
    if (rank == 0) {
        bool check = Check(array, 2, res, EPSILON);
        ASSERT_TRUE(check);
        std::cout << "paralel_time: " << t1 - t0 << std::endl;
        t0 = MPI_Wtime();
        posled(array, 2);
        t1 = MPI_Wtime();
        std::cout << "posled_time: " << t1 - t0 << std::endl;
    }
}

TEST(Parallel_MPI, TEST_5__) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int str = 3;
    double array[12] = { 2, -1, 7, 8, 2, 7, 0, 9, 7, -2, 8, 13 };
    double *res = new double[3];
    double t0, t1;
    t0 = MPI_Wtime();
    res = zhordan_gauss(array, str);
    t1 = MPI_Wtime();
    if (rank == 0) {
        bool check = Check(array, 3, res, EPSILON);
        ASSERT_TRUE(check);
        std::cout << "paralel_time: " << t1 - t0 << std::endl;
        t0 = MPI_Wtime();
        posled(array, 3);
        t1 = MPI_Wtime();
        std::cout << "posled_time: " << t1 - t0 << std::endl;
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
