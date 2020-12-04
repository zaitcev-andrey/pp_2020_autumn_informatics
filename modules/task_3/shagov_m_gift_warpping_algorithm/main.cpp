// Copyright 2020 Shagov Maksim
#include <mpi.h>
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include "../../../modules/task_3/shagov_m_gift_warpping_algorithm/gift_warpping_algorithm.h"

TEST(Parallel_Gift_Warpping_Algorithm_MPI, Test_Random_Vector_Size_13) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int count_size_string = 13;
    std::vector<Point> points_1(count_size_string);
    std::vector<Point> points_2(count_size_string);
    std::vector<int> points_1_x;
    std::vector<int> points_1_y;
    std::vector<int> points_2_x;
    std::vector<int> points_2_y;

    if (rank == 0) {
        points_1 = createRandomPoints(count_size_string);
        points_2 = points_1;
    }

    points_1 = buildConvexHullParallel(points_1);

    if (rank == 0) {
        for (size_t i = 0; i < points_1.size(); i++) {
            points_1_x.push_back(points_1[i].x);
            points_1_y.push_back(points_1[i].y);
        }
        double startT = MPI_Wtime();
        points_2 = buildConvexHull(points_2);
        double endT = MPI_Wtime();
        for (size_t i = 0; i < points_2.size(); i++) {
            points_2_x.push_back(points_2[i].x);
            points_2_y.push_back(points_2[i].y);
        }
        std::cout << "Consistent time: " << endT - startT << std::endl;
        ASSERT_EQ(points_1_x, points_2_x);
        ASSERT_EQ(points_1_y, points_2_y);
    }
}

TEST(Parallel_Gift_Warpping_Algorithm_MPI, Test_Random_Vector_Size_100) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int count_size_string = 100;
    std::vector<Point> points_1(count_size_string);
    std::vector<Point> points_2(count_size_string);
    std::vector<int> points_1_x;
    std::vector<int> points_1_y;
    std::vector<int> points_2_x;
    std::vector<int> points_2_y;

    if (rank == 0) {
        points_1 = createRandomPoints(count_size_string);
        points_2 = points_1;
    }

    points_1 = buildConvexHullParallel(points_1);

    if (rank == 0) {
        for (size_t i = 0; i < points_1.size(); i++) {
            points_1_x.push_back(points_1[i].x);
            points_1_y.push_back(points_1[i].y);
        }
        double startT = MPI_Wtime();
        points_2 = buildConvexHull(points_2);
        double endT = MPI_Wtime();
        for (size_t i = 0; i < points_2.size(); i++) {
            points_2_x.push_back(points_2[i].x);
            points_2_y.push_back(points_2[i].y);
        }
        std::cout << "Consistent time: " << endT - startT << std::endl;
        ASSERT_EQ(points_1_x, points_2_x);
        ASSERT_EQ(points_1_y, points_2_y);
    }
}

TEST(Parallel_Gift_Warpping_Algorithm_MPI, Test_Random_Vector_Size_1000) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int count_size_string = 1000;
    std::vector<Point> points_1(count_size_string);
    std::vector<Point> points_2(count_size_string);
    std::vector<int> points_1_x;
    std::vector<int> points_1_y;
    std::vector<int> points_2_x;
    std::vector<int> points_2_y;

    if (rank == 0) {
        points_1 = createRandomPoints(count_size_string);
        points_2 = points_1;
    }

    points_1 = buildConvexHullParallel(points_1);

    if (rank == 0) {
        for (size_t i = 0; i < points_1.size(); i++) {
            points_1_x.push_back(points_1[i].x);
            points_1_y.push_back(points_1[i].y);
        }
        double startT = MPI_Wtime();
        points_2 = buildConvexHull(points_2);
        double endT = MPI_Wtime();
        for (size_t i = 0; i < points_2.size(); i++) {
            points_2_x.push_back(points_2[i].x);
            points_2_y.push_back(points_2[i].y);
        }
        std::cout << "Consistent time: " << endT - startT << std::endl;
        ASSERT_EQ(points_1_x, points_2_x);
        ASSERT_EQ(points_1_y, points_2_y);
    }
}

TEST(Parallel_Gift_Warpping_Algorithm_MPI, Test_Random_Vector_Size_10000) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int count_size_string = 10000;
    std::vector<Point> points_1(count_size_string);
    std::vector<Point> points_2(count_size_string);
    std::vector<int> points_1_x;
    std::vector<int> points_1_y;
    std::vector<int> points_2_x;
    std::vector<int> points_2_y;

    if (rank == 0) {
        points_1 = createRandomPoints(count_size_string);
        points_2 = points_1;
    }

    points_1 = buildConvexHullParallel(points_1);

    if (rank == 0) {
        for (size_t i = 0; i < points_1.size(); i++) {
            points_1_x.push_back(points_1[i].x);
            points_1_y.push_back(points_1[i].y);
        }
        double startT = MPI_Wtime();
        points_2 = buildConvexHull(points_2);
        double endT = MPI_Wtime();
        for (size_t i = 0; i < points_2.size(); i++) {
            points_2_x.push_back(points_2[i].x);
            points_2_y.push_back(points_2[i].y);
        }
        std::cout << "Consistent time: " << endT - startT << std::endl;
        ASSERT_EQ(points_1_x, points_2_x);
        ASSERT_EQ(points_1_y, points_2_y);
    }
}

TEST(Parallel_Gift_Warpping_Algorithm_MPI, Test_Random_Vector_Size_1234) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int count_size_string = 1234;
    std::vector<Point> points_1(count_size_string);
    std::vector<Point> points_2(count_size_string);
    std::vector<int> points_1_x;
    std::vector<int> points_1_y;
    std::vector<int> points_2_x;
    std::vector<int> points_2_y;

    if (rank == 0) {
        points_1 = createRandomPoints(count_size_string);
        points_2 = points_1;
    }

    points_1 = buildConvexHullParallel(points_1);

    if (rank == 0) {
        for (size_t i = 0; i < points_1.size(); i++) {
            points_1_x.push_back(points_1[i].x);
            points_1_y.push_back(points_1[i].y);
        }
        double startT = MPI_Wtime();
        points_2 = buildConvexHull(points_2);
        double endT = MPI_Wtime();
        for (size_t i = 0; i < points_2.size(); i++) {
            points_2_x.push_back(points_2[i].x);
            points_2_y.push_back(points_2[i].y);
        }
        std::cout << "Consistent time: " << endT - startT << std::endl;
        ASSERT_EQ(points_1_x, points_2_x);
        ASSERT_EQ(points_1_y, points_2_y);
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
