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
    for (int& i : data) {
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


TEST(MPI_Scatter, float_to_float) {
    const int root = 0;
    int rank, size;
    float k = 3.3;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<float> data(20);
    std::vector<float> data1(20);
    std::vector<float> data2(20);
    std::vector<float> recv(data.size() / size);
    std::vector<float> scatter(data.size() / size);
    for (float& i : data) {
        i = ++k;
    }
    My_Scatter(data.data(), data.size() / size, MPI_FLOAT, recv.data(),
               data.size() / size, MPI_FLOAT, root, MPI_COMM_WORLD);
    MPI_Scatter(data.data(), data.size() / size, MPI_FLOAT, scatter.data(),
               data.size() / size, MPI_FLOAT, root, MPI_COMM_WORLD);
    MPI_Gather(recv.data(), recv.size(), MPI_FLOAT,
        data1.data(), recv.size(), MPI_FLOAT, root, MPI_COMM_WORLD);
    MPI_Gather(scatter.data(), scatter.size(), MPI_FLOAT,
        data2.data(), scatter.size(), MPI_FLOAT, root, MPI_COMM_WORLD);

    if (rank == root) {
        ASSERT_EQ(data1, data2);
    }
}

TEST(MPI_Scatter, double_to_double) {
    const int root = 0;
    int rank, size;
    double k = 17.3;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<double> data(20);
    std::vector<double> data1(20);
    std::vector<double> data2(20);
    std::vector<double> recv(data.size() / size);
    std::vector<double> scatter(data.size() / size);
    for (double& i : data) {
        i = ++k;
    }
    My_Scatter(data.data(), data.size() / size, MPI_DOUBLE, recv.data(),
               data.size() / size, MPI_DOUBLE, root, MPI_COMM_WORLD);
    MPI_Scatter(data.data(), data.size() / size, MPI_DOUBLE, scatter.data(),
               data.size() / size, MPI_DOUBLE, root, MPI_COMM_WORLD);
    MPI_Gather(recv.data(), recv.size(), MPI_DOUBLE,
        data1.data(), recv.size(), MPI_DOUBLE, root, MPI_COMM_WORLD);
    MPI_Gather(scatter.data(), scatter.size(), MPI_DOUBLE,
        data2.data(), scatter.size(), MPI_DOUBLE, root, MPI_COMM_WORLD);

    if (rank == root) {
        ASSERT_EQ(data1, data2);
    }
}
TEST(MPI_Scatter, char_to_char) {
    const int root = 0;
    int rank, size;
    char k = '1';
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<char> data(20);
    std::vector<char> data1(20);
    std::vector<char> data2(20);
    std::vector<char> recv(data.size() / size);
    std::vector<char> scatter(data.size() / size);
    for (char& i : data) {
        i = ++k;
    }
    My_Scatter(data.data(), data.size() / size, MPI_CHAR, recv.data(),
               data.size() / size, MPI_CHAR, root, MPI_COMM_WORLD);
    MPI_Scatter(data.data(), data.size() / size, MPI_CHAR, scatter.data(),
               data.size() / size, MPI_CHAR, root, MPI_COMM_WORLD);
    MPI_Gather(recv.data(), recv.size(), MPI_CHAR,
        data1.data(), recv.size(), MPI_CHAR, root, MPI_COMM_WORLD);
    MPI_Gather(scatter.data(), scatter.size(), MPI_CHAR,
        data2.data(), scatter.size(), MPI_CHAR, root, MPI_COMM_WORLD);

    if (rank == root) {
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