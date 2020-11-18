// Copyright 2020 Solovev Alexandr
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <random>
#include <vector>
#include "../../../modules/task_2/solovev_a_scatter/scatter.h"

TEST(MPI_Scatter, int_to_int) {
    const int root = 0;
    int rank, size;
    int k = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<int> data(20);
    std::vector<int> data1(20);
    std::vector<int> data2(20);
    std::vector<int> recv(data.size() / size);
    std::vector<int> scatter(data.size() / size);
    for (std::vector<int>::iterator it = data.begin(); it!= data.end(); ++it) {
        int& i = *it;
        i = ++k;
	}
    My_Scatter(data.data(), data.size() / size, MPI_INT, recv.data(),
               data.size() / size, MPI_INT, root, MPI_COMM_WORLD);
    MPI_Scatter(data.data(), data.size() / size, MPI_INT, scatter.data(),
               data.size() / size, MPI_INT, root, MPI_COMM_WORLD);
    MPI_Gather(recv.data(), recv.size(), MPI_INT,
        data1.data(), recv.size(), MPI_INT, root, MPI_COMM_WORLD);
    MPI_Gather(scatter.data(), scatter.size(), MPI_INT,
        data2.data(), scatter.size(), MPI_INT, root, MPI_COMM_WORLD);

    if (rank == root) {
        ASSERT_EQ(data1, data2);
    }
}


TEST(MPI_Scatter, float) {
    const int root = 0;
    int rank, size;
    float k = 1.2;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<float> data(12);
    std::vector<float> data1(12 * 2);
    std::vector<float> data2(12 * 2);
    std::vector<float> recv((data.size() / size) * (sizeof(double) / sizeof(float)));
    std::vector<float> scatter(recv.size());

    for (std::vector<float>::iterator it = data.begin(); it!= data.end(); ++it) {
        float& i = *it;
        i = ++k;
	}


    My_Scatter(data.data(), data.size() / size, MPI_DOUBLE, recv.data(),
               recv.size(), MPI_FLOAT, root, MPI_COMM_WORLD);
    MPI_Scatter(data.data(), data.size() / size, MPI_DOUBLE, scatter.data(),
                recv.size(), MPI_FLOAT, root, MPI_COMM_WORLD);
    MPI_Gather(recv.data(), recv.size(), MPI_FLOAT,
        data1.data(), recv.size(), MPI_FLOAT, root, MPI_COMM_WORLD);
    MPI_Gather(scatter.data(), scatter.size(), MPI_FLOAT,
        data2.data(), scatter.size(), MPI_FLOAT, root, MPI_COMM_WORLD);
    if (rank == 0) {
        ASSERT_EQ(data1, data2);
    }
}
TEST(MPI_Scatter, throw_when_error_count_and_root) {
    const int root = -1;

    std::vector<int> data(1000);
    std::vector<int> data1(1000);
    std::vector<int> data2(1000);
    std::vector<int> recv;
    std::vector<int> scatter;

    ASSERT_EQ(MPI_ERR_COUNT);
}
TEST(MPI_Scatter, char) {
    const int root = 0;
    int rank, size;
    char k = 'a';
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<char> data(4 * size * size);
    std::vector<char> data1(4 * size * size / 4);
    std::vector<char> data2(4 * size * size / 4);
    std::vector<char> recv;
    std::vector<char> scatter;

    for (std::vector<char>::iterator it = data.begin(); it!= data.end(); ++it) {
        char& i = *it;
        i = ++k;
}

    recv.resize((data.size() / size) / 4);
    scatter.resize(recv.size());

    My_Scatter(data.data(), data.size() / size, MPI_CHAR, recv.data(), recv.size(), MPI_INT, root, MPI_COMM_WORLD);
    MPI_Scatter(data.data(), data.size() / size, MPI_CHAR, scatter.data(), recv.size(), MPI_INT, root, MPI_COMM_WORLD);

    MPI_Gather(recv.data(), recv.size(), MPI_INT,
        data1.data(), recv.size(), MPI_INT, root, MPI_COMM_WORLD);
    MPI_Gather(scatter.data(), scatter.size(), MPI_INT,
        data2.data(), scatter.size(), MPI_INT, root, MPI_COMM_WORLD);
    if (rank == 0) {
        ASSERT_EQ(data1, data2);
    }
}
TEST(MPI_Scatter, double) {
    const int root = 0;
    int rank, size;
    double k = 1.2;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<double> data(12);
    std::vector<double> data1(12 * 2);
    std::vector<double> data2(12 * 2);
    std::vector<double> scatter;
	std::vector<double> recv;
    for (std::vector<double>::iterator it = data.begin(); it!= data.end(); ++it) {
        double& i = *it;
        i = ++k;
}

    recv.resize((data.size() / size) * (sizeof(double) / sizeof(int)));
    scatter.resize(recv.size());

    My_Scatter(data.data(), data.size() / size, MPI_DOUBLE, recv.data(),
               recv.size(), MPI_INT, root, MPI_COMM_WORLD);
    MPI_Scatter(data.data(), data.size() / size, MPI_DOUBLE, scatter.data(),
               recv.size(), MPI_INT, root, MPI_COMM_WORLD);
    MPI_Gather(recv.data(), recv.size(), MPI_INT,
        data1.data(), recv.size(), MPI_INT, root, MPI_COMM_WORLD);
    MPI_Gather(scatter.data(), scatter.size(), MPI_INT,
        data2.data(), scatter.size(), MPI_INT, root, MPI_COMM_WORLD);
    if (rank == 0) {
        ASSERT_EQ(data1, data2);
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
