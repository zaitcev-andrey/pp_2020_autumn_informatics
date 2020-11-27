// Copyright 2020 Tarasov Nikita
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <random>
#include "../../../modules/task_2/tarasov_n_change_contrast/change_contrast.h"

TEST(Increase_contrast_MPI, test1) {
    int mpirank;
    MPI_Comm_rank(MPI_COMM_WORLD, &mpirank);
    if (mpirank == 0) {
        ASSERT_ANY_THROW(set_random_img(-1, 3));
    }
}

TEST(Increase_contrast_MPI, test2) {
    std::vector <int> a;
    int contrast = 20;
    int mpirank;
    MPI_Comm_rank(MPI_COMM_WORLD, &mpirank);
    if (mpirank == 0) {
        a = set_random_img(5, 7);
        ASSERT_ANY_THROW(changeContrastParallel(a, 3, 2, contrast));
    }
}

TEST(Increase_contrast_MPI, test3) {
    int width = 3, high = 3, contrast = 20;
    std::vector <int> a(width * high), ans_seq(width * high);
    int mpirank;
    MPI_Comm_rank(MPI_COMM_WORLD, &mpirank);
    if (mpirank == 0) {
        a[0] = 178;
        a[1] = 151;
        a[2] = 118;
        a[3] = 238;
        a[4] = 208;
        a[5] = 118;
        a[6] = 58;
        a[7] = 255;
        a[8] = 238;
        ans_seq[0] = 212;
        ans_seq[1] = 179;
        ans_seq[2] = 140;
        ans_seq[3] = 255;
        ans_seq[4] = 248;
        ans_seq[5] = 140;
        ans_seq[6] = 68;
        ans_seq[7] = 255;
        ans_seq[8] = 255;
    }
    std::vector <int> ans(width * high);
    ans = changeContrastParallel(a, width, high, contrast);
    if (mpirank == 0) {
        ASSERT_EQ(ans_seq, ans);
    }
}

TEST(Increase_contrast_MPI, test4) {
    int width = 3, high = 3, contrast = 60;
    std::vector <int> a(width * high), ans_seq(width * high);
    int mpirank;
    MPI_Comm_rank(MPI_COMM_WORLD, &mpirank);
    if (mpirank == 0) {
        a[0] = 150;
        a[1] = 128;
        a[2] = 100;
        a[3] = 200;
        a[4] = 175;
        a[5] = 100;
        a[6] = 50;
        a[7] = 250;
        a[8] = 200;
        ans_seq[0] = 150;
        ans_seq[1] = 114;
        ans_seq[2] = 70;
        ans_seq[3] = 230;
        ans_seq[4] = 190;
        ans_seq[5] = 70;
        ans_seq[6] = 0;
        ans_seq[7] = 255;
        ans_seq[8] = 230;
    }
    std::vector <int> ans(width * high);
    ans = changeContrast(a, width, high, contrast);
    if (mpirank == 0) {
        ASSERT_EQ(ans_seq, ans);
    }
}

TEST(Increase_contrast_MPI, test5) {
    int width = 200, high = 150, contrast = 20;
    std::vector <int> a(width * high);
    int mpirank;
    MPI_Comm_rank(MPI_COMM_WORLD, &mpirank);
    if (mpirank == 0) {
        a = set_random_img(width, high);
    }
    std::vector <int> ans(width * high);
    ans = changeContrastParallel(a, width, high, contrast);
    std::vector <int> ans_seq(width * high);
    if (mpirank == 0) {
        ans_seq = changeContrast(a, width, high, contrast);
        ASSERT_EQ(ans_seq, ans);
    }
}

TEST(Increase_contrast_MPI, test6) {
    int width = 1000, high = 800, contrast = 80;
    std::vector <int> a(width * high);
    int mpirank;
    MPI_Comm_rank(MPI_COMM_WORLD, &mpirank);
    if (mpirank == 0) {
        a = set_random_img(width, high);
    }
    std::vector <int> ans(width * high);
    ans = changeContrastParallel(a, width, high, contrast);
    std::vector <int> ans_seq(width * high);
    if (mpirank == 0) {
        ans_seq = changeContrast(a, width, high, contrast);
        ASSERT_EQ(ans_seq, ans);
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
