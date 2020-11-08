// Copyright 2020 Volkova Anastasia
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <random>
#include "./scatter_mpi.h"

using namespace std; 

TEST(MY_SCATTER, INT_ERROR_COUNT) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int k = 6;
    int ROOT = 3;
    int aSize = k * size;
    vector<int> a(aSize);
    int b1[k];
    int b2[k];
    if (rank == ROOT) {
        for (int i = 0; i < aSize; ++i) a[i] = i;
    }
    if (rank == ROOT) {
        EXPECT_EQ(MY_Scatter(&a[0], k, MPI_INT, &b1[0], 10, MPI_INT, ROOT, MPI_COMM_WORLD), MPI_ERR_COUNT);
    }
}

TEST(MY_SCATTER, DOUBLE_ERROR_RANK) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int k = 16;
    int ROOT = 3;
    int aSize = k * size;
    vector<double> a(aSize);
    double b1[k];
    if (rank == ROOT) {
        for (int i = 0; i < aSize; ++i) a[i] = i*0.5+i*0.1/3;
    }
    if (rank == ROOT) {
        EXPECT_EQ(MY_Scatter(&a[0], k, MPI_DOUBLE, &b1[0], k, MPI_DOUBLE, -1, MPI_COMM_WORLD), MPI_ERR_ROOT);
    }
}


TEST(MY_SCATTER, INT) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int k = 6;
    int ROOT = 1;
    int aSize = k * size;
    vector<int> a(aSize);
    int b1[k];
    int b2[k];
    if (rank == ROOT) {
        for (int i = 0; i < aSize; ++i) a[i] = i;
    }
    double myScatterStart = MPI_Wtime();
    MY_Scatter(&a[0], k, MPI_INT, &b1[0], k, MPI_INT, ROOT, MPI_COMM_WORLD);
    double myScatterEnd = MPI_Wtime();
    cout << "my scatter :   " << myScatterEnd - myScatterStart << '\n';
    double mpiScatterStart = MPI_Wtime();
    MPI_Scatter(&a[0], k, MPI_INT, &b2[0], k, MPI_INT, ROOT, MPI_COMM_WORLD);
    double mpiScatterEnd = MPI_Wtime();
    cout << "mpi scatter :   " << mpiScatterEnd - mpiScatterStart << '\n';

    if (rank == ROOT) {
        EXPECT_EQ(b1[0], b2[0]);
    }
}

TEST(MY_SCATTER, DOUBLE) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int k = 7;
    int ROOT = 4;
    int aSize = k * size;
    vector<double> a(aSize);
    double b1[k];
    double b2[k];
    if (rank == ROOT) {
        for (int i = 0; i < aSize; ++i) a[i] = i + 0.1*(i+1);
    }
    double myScatterStart = MPI_Wtime();
    MY_Scatter(&a[0], k, MPI_DOUBLE, &b1[0], k, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);
    double myScatterEnd = MPI_Wtime();
    cout << "my scatter :   " << myScatterEnd - myScatterStart << '\n';
    double mpiScatterStart = MPI_Wtime();
    MPI_Scatter(&a[0], k, MPI_DOUBLE, &b2[0], k, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);
    double mpiScatterEnd = MPI_Wtime();
    cout << "mpi scatter :   " << mpiScatterEnd - mpiScatterStart << '\n';
    if (rank == ROOT) {
        EXPECT_EQ(b1[0], b2[0]);
    }
}

TEST(MY_SCATTER, FLOAT) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int k = 5;
    int ROOT = 1;
    int aSize = k * size;
    vector<float> a(aSize);
    float b1[k];
    float b2[k];
    if (rank == ROOT) {
        for (int i = 0; i < aSize; ++i) a[i] = i + 0.1 * (i + 1);
    }
    double myScatterStart = MPI_Wtime();
    MY_Scatter(&a[0], k, MPI_FLOAT, &b1[0], k, MPI_FLOAT, ROOT, MPI_COMM_WORLD);
    double myScatterEnd = MPI_Wtime();
    cout << "my scatter :   " << myScatterEnd - myScatterStart << '\n';
    double mpiScatterStart = MPI_Wtime();
    MPI_Scatter(&a[0], k, MPI_FLOAT, &b2[0], k, MPI_FLOAT, ROOT, MPI_COMM_WORLD);
    double mpiScatterEnd = MPI_Wtime();
    cout << "mpi scatter :   " << mpiScatterEnd - mpiScatterStart << '\n';
    if (rank == ROOT) {
        EXPECT_EQ(b1[0], b2[0]);
    }
}

TEST(MY_SCATTER, CHAR) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int k = 20;
    int ROOT = 1;
    int aSize = k * size;
    vector<char> a(aSize);
    char b1[k];
    char b2[k];
    mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    int symbol;
    if (rank == ROOT) {
        for (int i = 0; i < aSize; ++i) {
            symbol = gen() % 255;
            a[i] = static_cast<char>(symbol);
        }
    }
    double myScatterStart = MPI_Wtime();
    MY_Scatter(&a[0], k, MPI_CHAR, &b1[0], k, MPI_CHAR, ROOT, MPI_COMM_WORLD);
    double myScatterEnd = MPI_Wtime();
    cout << "my scatter :   " << myScatterEnd - myScatterStart << '\n';
    double mpiScatterStart = MPI_Wtime();
    MPI_Scatter(&a[0], k, MPI_CHAR, &b2[0], k, MPI_CHAR, ROOT, MPI_COMM_WORLD);
    double mpiScatterEnd = MPI_Wtime();
    cout << "mpi scatter :   " << mpiScatterEnd - mpiScatterStart << '\n';
    if (rank == ROOT) {
        EXPECT_EQ(b1[0], b2[0]);
    }
}

TEST(MY_SCATTER, INT_SCATTER_GATHER) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int k = 6;
    int ROOT = 3;
    int aSize = k * size;
    vector<int> a(aSize);
    vector<int> ans(aSize);
    int b1[k];
    if (rank == ROOT) {
        for (int i = 0; i < aSize; ++i) a[i] = i;
    }
    double myScatterStart = MPI_Wtime();
    MY_Scatter(&a[0], k, MPI_INT, &b1[0], k, MPI_INT, ROOT, MPI_COMM_WORLD);
    double myScatterEnd = MPI_Wtime();
    cout << "my scatter :   " << myScatterEnd - myScatterStart << '\n';
    double mpiScatterStart = MPI_Wtime();
    MPI_Gather(&b1[0], k, MPI_INT, &ans[0], k, MPI_INT, ROOT, MPI_COMM_WORLD);
    double mpiScatterEnd = MPI_Wtime();
    cout << "mpi scatter :   " << mpiScatterEnd - mpiScatterStart << '\n';
    if (rank == ROOT) {
        EXPECT_EQ(a, ans);
    }
}

TEST(MY_SCATTER, DOUBLE_SCATTER_GATHER) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int k = 10;
    int ROOT = 0;
    int aSize = k * size;
    vector<double> a(k * size);
    vector<double> ans(k * size);
    double b1[k];
    if (rank == ROOT) {
        for (int i = 0; i < aSize; ++i) a[i] = i + 0.1 * (i + 1);
    }
    double myScatterStart = MPI_Wtime();
    MY_Scatter(&a[0], k, MPI_DOUBLE, &b1[0], k, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);
    double myScatterEnd = MPI_Wtime();
    cout << "my scatter :   " << myScatterEnd - myScatterStart << '\n';
    double mpiScatterStart = MPI_Wtime();
    MPI_Gather(&b1[0], k, MPI_DOUBLE, &ans[0], k, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);
    double mpiScatterEnd = MPI_Wtime();
    cout << "mpi scatter :   " << mpiScatterEnd - mpiScatterStart << '\n';
    if (rank == ROOT) {
        EXPECT_EQ(a, ans);
    }
}

TEST(MY_SCATTER, FLOAT_SCATTER_GATHER) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int k = 10;
    int ROOT = 0;
    int aSize = k * size;
    vector<float> a(aSize);
    vector<float> ans(aSize);
    float b1[k];
    if (rank == ROOT) {
        for (int i = 0; i < aSize; ++i) a[i] = i + 0.1 * (i + 1);
    }
    double myScatterStart = MPI_Wtime();
    MY_Scatter(&a[0], k, MPI_FLOAT, &b1[0], k, MPI_FLOAT, ROOT, MPI_COMM_WORLD);
    double myScatterEnd = MPI_Wtime();
    cout << "my scatter :   " << myScatterEnd - myScatterStart << '\n';
    double mpiScatterStart = MPI_Wtime();
    MPI_Gather(&b1[0], k, MPI_FLOAT, &ans[0], k, MPI_FLOAT, ROOT, MPI_COMM_WORLD);
    double mpiScatterEnd = MPI_Wtime();
    cout << "mpi scatter :   " << mpiScatterEnd - mpiScatterStart << '\n';
    if (rank == ROOT) {
        EXPECT_EQ(a, ans);
    }
}

TEST(MY_SCATTER, CHAR_SCATTER_GATHER) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int k = 20;
    int ROOT = 1;
    int aSize = k * size;
    vector<char> a(aSize);
    vector<char> ans(aSize);
    char b1[k];
    mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    int symbol;
    if (rank == ROOT) {
        for (int i = 0; i < k * size; ++i) {
            symbol = gen() % 255;
            a[i] = static_cast<char>(symbol);
        }
    }
    double myScatterStart = MPI_Wtime();
    MY_Scatter(&a[0], k, MPI_CHAR, &b1[0], k, MPI_CHAR, ROOT, MPI_COMM_WORLD);
    double myScatterEnd = MPI_Wtime();
    cout << "my scatter :   " << myScatterEnd - myScatterStart << '\n';
    double mpiScatterStart = MPI_Wtime();
    MPI_Gather(&b1[0], k, MPI_CHAR, &ans[0], k, MPI_CHAR, ROOT, MPI_COMM_WORLD);
    double mpiScatterEnd = MPI_Wtime();
    cout << "mpi scatter :   " << mpiScatterEnd - mpiScatterStart << '\n';
    if (rank == ROOT) {
        EXPECT_EQ(a, ans);
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
