// Copyright 2020 Volkova Anastasia
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <random>
#include <vector>
#include "./scatter_mpi.h"

TEST(MY_SCATTER, INT_ERROR_COUNT) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int k = 61;
    int ROOT = 3;
    int aSize = k * size;
    std::vector<int> a(aSize);
    int b1[61];
    int b2[61];
    if (rank == ROOT) {
        for (int i = 0; i < aSize; ++i) a[i] = i + 18 * i;
    }
    if (rank == ROOT) {
        EXPECT_EQ(MY_Scatter(&a[0], k, MPI_INT, &b1[0], 10, MPI_INT, ROOT, MPI_COMM_WORLD), MPI_ERR_COUNT);
    }
}

TEST(MY_SCATTER, DOUBLE_ERROR_RANK) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int k = 16;
    int ROOT = 3;
    int aSize = k * size;
    std::vector<double> a(aSize);
    double b1[6];
    if (rank == ROOT) {
        for (int i = 0; i < aSize; ++i) a[i] = i*0.5+i*0.1/3;
    }
    if (rank == ROOT) {
        EXPECT_EQ(MY_Scatter(&a[0], k, MPI_DOUBLE, &b1[0], k, MPI_DOUBLE, -1, MPI_COMM_WORLD), MPI_ERR_ROOT);
    }
}

TEST(MY_SCATTER, INT_ERROR_BUFFER) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int k = 61;
    int ROOT = 3;
    std::vector<int> a;
    int b1[61];
    if (rank == ROOT) {
        EXPECT_EQ(MY_Scatter(&a[0], k, MPI_INT, &b1[0], k, MPI_INT, ROOT, MPI_COMM_WORLD), MPI_ERR_BUFFER);
    }
}

TEST(MY_SCATTER, INT) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int k = 6;
    int ROOT = 1;
    int aSize = k * size;
    std::vector<int> a(aSize);
    int b1[6];
    int b2[6];
    if (rank == ROOT) {
        for (int i = 0; i < aSize; ++i) a[i] = i + 18 * i;
    }

    double myScatterStart = MPI_Wtime();
    MY_Scatter(&a[0], k, MPI_INT, &b1[0], k, MPI_INT, ROOT, MPI_COMM_WORLD);
    double myScatterEnd = MPI_Wtime();

    double mpiScatterStart = MPI_Wtime();
    MPI_Scatter(&a[0], k, MPI_INT, &b2[0], k, MPI_INT, ROOT, MPI_COMM_WORLD);
    double mpiScatterEnd = MPI_Wtime();

    if (rank == ROOT) {
        for (int i = 0; i < k; ++i) {
            ASSERT_EQ(b1[i], b2[i]);
        }
    }
    if (rank == 0) {
        std::cout << "my scatter :   " << myScatterEnd - myScatterStart << std::endl;
        std::cout << "mpi scatter :   " << mpiScatterEnd - mpiScatterStart << std::endl;
    }
}

TEST(MY_SCATTER, DOUBLE) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int k = 7;
    int ROOT = 4;
    int aSize = k * size;
    std::vector<double> a(aSize);
    double b1[7];
    double b2[7];
    if (rank == ROOT) {
        for (int i = 0; i < aSize; ++i) a[i] = i + 0.1*(i+1);
    }

    double myScatterStart = MPI_Wtime();
    MY_Scatter(&a[0], k, MPI_DOUBLE, &b1[0], k, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);
    double myScatterEnd = MPI_Wtime();

    double mpiScatterStart = MPI_Wtime();
    MPI_Scatter(&a[0], k, MPI_DOUBLE, &b2[0], k, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);
    double mpiScatterEnd = MPI_Wtime();

    if (rank == ROOT) {
        for (int i = 0; i < k; ++i) {
            ASSERT_EQ(b1[i], b2[i]);
        }
    }
    if (rank == 0) {
        std::cout << "my scatter :   " << myScatterEnd - myScatterStart << std::endl;
        std::cout << "mpi scatter :   " << mpiScatterEnd - mpiScatterStart << std::endl;
    }
}

TEST(MY_SCATTER, FLOAT) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int k = 5;
    int ROOT = 1;
    int aSize = k * size;
    std::vector<float> a(aSize);
    float b1[5];
    float b2[5];
    if (rank == ROOT) {
        for (int i = 0; i < aSize; ++i) a[i] = i + 0.1 * (i + 1);
    }

    double myScatterStart = MPI_Wtime();
    MY_Scatter(&a[0], k, MPI_FLOAT, &b1[0], k, MPI_FLOAT, ROOT, MPI_COMM_WORLD);
    double myScatterEnd = MPI_Wtime();

    double mpiScatterStart = MPI_Wtime();
    MPI_Scatter(&a[0], k, MPI_FLOAT, &b2[0], k, MPI_FLOAT, ROOT, MPI_COMM_WORLD);
    double mpiScatterEnd = MPI_Wtime();

    if (rank == ROOT) {
        for (int i = 0; i < k; ++i) {
            ASSERT_EQ(b1[i], b2[i]);
        }
    }
    if (rank == 0) {
        std::cout << "my scatter :   " << myScatterEnd - myScatterStart << std::endl;
        std::cout << "mpi scatter :   " << mpiScatterEnd - mpiScatterStart << std::endl;
    }
}

TEST(MY_SCATTER, CHAR) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int k = 20;
    int ROOT = 1;
    int aSize = k * size;
    std::vector<char> a(aSize);
    char b1[20];
    char b2[20];
    std::mt19937 gen;
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

    double mpiScatterStart = MPI_Wtime();
    MPI_Scatter(&a[0], k, MPI_CHAR, &b2[0], k, MPI_CHAR, ROOT, MPI_COMM_WORLD);
    double mpiScatterEnd = MPI_Wtime();

    if (rank == ROOT) {
        for (int i = 0; i < k; ++i) {
            ASSERT_EQ(b1[i], b2[i]);
        }
    }
    if (rank == 0) {
        std::cout << "my scatter :   " << myScatterEnd - myScatterStart << std::endl;
        std::cout << "mpi scatter :   " << mpiScatterEnd - mpiScatterStart << std::endl;
    }
}

TEST(MY_SCATTER, INT_SCATTER_GATHER) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int k = 6;
    int ROOT = 3;
    int aSize = k * size;
    std::vector<int> a(aSize);
    std::vector<int> ans(aSize);
    int b1[6];
    if (rank == ROOT) {
        for (int i = 0; i < aSize; ++i) a[i] = i + 18 * i;
    }

    MY_Scatter(&a[0], k, MPI_INT, &b1[0], k, MPI_INT, ROOT, MPI_COMM_WORLD);
    MPI_Gather(&b1[0], k, MPI_INT, &ans[0], k, MPI_INT, ROOT, MPI_COMM_WORLD);
    if (rank == ROOT) {
        EXPECT_EQ(a, ans);
    }
}

TEST(MY_SCATTER, DOUBLE_SCATTER_GATHER) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int k = 10;
    int ROOT = 0;
    int aSize = k * size;
    std::vector<double> a(k * size);
    std::vector<double> ans(k * size);
    double b1[10];
    if (rank == ROOT) {
        for (int i = 0; i < aSize; ++i) a[i] = i + 0.1 * (i + 1);
    }

    MY_Scatter(&a[0], k, MPI_DOUBLE, &b1[0], k, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);
    MPI_Gather(&b1[0], k, MPI_DOUBLE, &ans[0], k, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);
    if (rank == ROOT) {
        EXPECT_EQ(a, ans);
    }
}

TEST(MY_SCATTER, FLOAT_SCATTER_GATHER) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int k = 10;
    int ROOT = 0;
    int aSize = k * size;
    std::vector<float> a(aSize);
    std::vector<float> ans(aSize);
    float b1[10];
    if (rank == ROOT) {
        for (int i = 0; i < aSize; ++i) a[i] = i + 0.1 * (i + 1);
    }

    MY_Scatter(&a[0], k, MPI_FLOAT, &b1[0], k, MPI_FLOAT, ROOT, MPI_COMM_WORLD);
    MPI_Gather(&b1[0], k, MPI_FLOAT, &ans[0], k, MPI_FLOAT, ROOT, MPI_COMM_WORLD);
    if (rank == ROOT) {
        EXPECT_EQ(a, ans);
    }
}

TEST(MY_SCATTER, CHAR_SCATTER_GATHER) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int k = 20;
    int ROOT = 1;
    int aSize = k * size;
    std::vector<char> a(aSize);
    std::vector<char> ans(aSize);
    char b1[20];
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    int symbol;
    if (rank == ROOT) {
        for (int i = 0; i < k * size; ++i) {
            symbol = gen() % 255;
            a[i] = static_cast<char>(symbol);
        }
    }

    MY_Scatter(&a[0], k, MPI_CHAR, &b1[0], k, MPI_CHAR, ROOT, MPI_COMM_WORLD);
    MPI_Gather(&b1[0], k, MPI_CHAR, &ans[0], k, MPI_CHAR, ROOT, MPI_COMM_WORLD);
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
