// Copyright 2020 Tkachev Alexey
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <limits>
#include "../../../../modules/task_2/tkachev_a_ribbon_horizontal_scheme/ribbon_horizontal_scheme.h"
using std::vector;

TEST(Ribbon_horizontal_scheme, MatrixTest_101_503) {
    int process_rank;
    int matrix_count_rows = 101, matrix_count_columns = 503;
    std::vector<int> test_matrix(matrix_count_rows * matrix_count_columns);

    std::vector<int> the_test_vector(matrix_count_columns);

    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    if (process_rank == 0) {
       test_matrix = getRandomVector(matrix_count_rows, matrix_count_columns);
       the_test_vector = getRandomVector(matrix_count_columns, 1);
    }

    std::vector<int> parallel_multiply_on_vector;

    double _time1 = MPI_Wtime();
    parallel_multiply_on_vector = parallelMultiplyOnVector(
                test_matrix, the_test_vector, matrix_count_rows, matrix_count_columns);
    double _time2 = MPI_Wtime();

    if (process_rank == 0) {
        printf("PARRALEL TIME: %.5f\n", _time2-_time1);
        std::vector<int> multiply_on_vector;
        _time1 = MPI_Wtime();
        multiply_on_vector = multiplyOnVector(test_matrix, the_test_vector,
        matrix_count_rows, matrix_count_columns);
        _time2 = MPI_Wtime();
        printf("NOT PARRALEL TIME %.5f\n", _time2-_time1);
        ASSERT_EQ(multiply_on_vector, parallel_multiply_on_vector);
    }
}

TEST(Ribbon_horizontal_scheme, MatrixTest_42_59) {
    int process_rank;
    int matrix_count_rows = 42, matrix_count_columns = 59;
    std::vector<int> test_matrix(matrix_count_rows * matrix_count_columns);

    std::vector<int> the_test_vector(matrix_count_columns);

    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    if (process_rank == 0) {
       test_matrix = getRandomVector(matrix_count_rows, matrix_count_columns);
       the_test_vector = getRandomVector(matrix_count_columns, 1);
    }

    std::vector<int> parallel_multiply_on_vector;

    double _time1 = MPI_Wtime();
    parallel_multiply_on_vector = parallelMultiplyOnVector(
                test_matrix, the_test_vector, matrix_count_rows, matrix_count_columns);
    double _time2 = MPI_Wtime();

    if (process_rank == 0) {
        printf("PARRALEL TIME: %.5f\n", _time2-_time1);
        std::vector<int> multiply_on_vector;
        _time1 = MPI_Wtime();
        multiply_on_vector = multiplyOnVector(test_matrix, the_test_vector,
        matrix_count_rows, matrix_count_columns);
        _time2 = MPI_Wtime();
        printf("NOT PARRALEL TIME %.5f\n", _time2-_time1);
        ASSERT_EQ(multiply_on_vector, parallel_multiply_on_vector);
    }
}

TEST(Ribbon_horizontal_scheme, MatrixTest_90_90) {
    int process_rank;
    int matrix_count_rows = 90, matrix_count_columns = 90;
    std::vector<int> test_matrix(matrix_count_rows * matrix_count_columns);

    std::vector<int> the_test_vector(matrix_count_columns);

    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    if (process_rank == 0) {
       test_matrix = getRandomVector(matrix_count_rows, matrix_count_columns);
       the_test_vector = getRandomVector(matrix_count_columns, 1);
    }

    std::vector<int> parallel_multiply_on_vector;

    double _time1 = MPI_Wtime();
    parallel_multiply_on_vector = parallelMultiplyOnVector(
                test_matrix, the_test_vector, matrix_count_rows, matrix_count_columns);
    double _time2 = MPI_Wtime();

    if (process_rank == 0) {
        printf("PARRALEL TIME: %.5f\n", _time2-_time1);
        std::vector<int> multiply_on_vector;
        _time1 = MPI_Wtime();
        multiply_on_vector = multiplyOnVector(test_matrix, the_test_vector,
        matrix_count_rows, matrix_count_columns);
        _time2 = MPI_Wtime();
        printf("NOT PARRALEL TIME %.5f\n", _time2-_time1);
        ASSERT_EQ(multiply_on_vector, parallel_multiply_on_vector);
    }
}


TEST(Ribbon_horizontal_scheme, MatrixTest_100_10) {
    int process_rank;
    int matrix_count_rows = 100, matrix_count_columns = 10;
    std::vector<int> test_matrix(matrix_count_rows * matrix_count_columns);

    std::vector<int> the_test_vector(matrix_count_columns);

    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    if (process_rank == 0) {
       test_matrix = getRandomVector(matrix_count_rows, matrix_count_columns);
       the_test_vector = getRandomVector(matrix_count_columns, 1);
    }

    std::vector<int> parallel_multiply_on_vector;

    double _time1 = MPI_Wtime();
    parallel_multiply_on_vector = parallelMultiplyOnVector(
                test_matrix, the_test_vector, matrix_count_rows, matrix_count_columns);
    double _time2 = MPI_Wtime();

    if (process_rank == 0) {
        printf("PARRALEL TIME: %.5f\n", _time2-_time1);
        std::vector<int> multiply_on_vector;
        _time1 = MPI_Wtime();
        multiply_on_vector = multiplyOnVector(test_matrix, the_test_vector,
        matrix_count_rows, matrix_count_columns);
        _time2 = MPI_Wtime();
        printf("NOT PARRALEL TIME: %.5f\n", _time2-_time1);
        ASSERT_EQ(multiply_on_vector, parallel_multiply_on_vector);
    }
}

TEST(Ribbon_horizontal_scheme, MatrixTest_135_67) {
    int process_rank;
    int matrix_count_rows = 135, matrix_count_columns = 67;
    std::vector<int> test_matrix(matrix_count_rows * matrix_count_columns);

    std::vector<int> the_test_vector(matrix_count_columns);

    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    if (process_rank == 0) {
       test_matrix = getRandomVector(matrix_count_rows, matrix_count_columns);
       the_test_vector = getRandomVector(matrix_count_columns, 1);
    }

    std::vector<int> parallel_multiply_on_vector;

    double _time1 = MPI_Wtime();
    parallel_multiply_on_vector = parallelMultiplyOnVector(
                test_matrix, the_test_vector, matrix_count_rows, matrix_count_columns);
    double _time2 = MPI_Wtime();

    if (process_rank == 0) {
        printf("PARRALEL TIME: %.5f\n", _time2-_time1);
        std::vector<int> multiply_on_vector;
        _time1 = MPI_Wtime();
        multiply_on_vector = multiplyOnVector(test_matrix, the_test_vector,
        matrix_count_rows, matrix_count_columns);
        _time2 = MPI_Wtime();
        printf("NOT PARRALEL TIME: %.5f\n", _time2-_time1);
        ASSERT_EQ(multiply_on_vector, parallel_multiply_on_vector);
    }
}

TEST(Ribbon_horizontal_scheme, MatrixTest_20_20) {
    int process_rank;
    int matrix_count_rows = 20, matrix_count_columns = 20;
    std::vector<int> test_matrix(matrix_count_rows * matrix_count_columns);

    std::vector<int> the_test_vector(matrix_count_columns);

    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    if (process_rank == 0) {
       test_matrix = getRandomVector(matrix_count_rows, matrix_count_columns);
       the_test_vector = getRandomVector(matrix_count_columns, 1);
    }

    std::vector<int> parallel_multiply_on_vector;

    double _time1 = MPI_Wtime();
    parallel_multiply_on_vector = parallelMultiplyOnVector(
                test_matrix, the_test_vector, matrix_count_rows, matrix_count_columns);
    double _time2 = MPI_Wtime();

    if (process_rank == 0) {
        printf("PARRALEL TIME: %.5f\n", _time2-_time1);
        std::vector<int> multiply_on_vector;
        _time1 = MPI_Wtime();
        multiply_on_vector = multiplyOnVector(test_matrix, the_test_vector,
        matrix_count_rows, matrix_count_columns);
        _time2 = MPI_Wtime();
        printf("NOT PARRALEL TIME: %.5f\n", _time2-_time1);
        ASSERT_EQ(multiply_on_vector, parallel_multiply_on_vector);
    }
}

TEST(Ribbon_horizontal_scheme, MatrixTest_150_151) {
    int process_rank;
    int matrix_count_rows = 150, matrix_count_columns = 151;
    std::vector<int> test_matrix(matrix_count_rows * matrix_count_columns);

    std::vector<int> the_test_vector(matrix_count_columns);

    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    if (process_rank == 0) {
       test_matrix = getRandomVector(matrix_count_rows, matrix_count_columns);
       the_test_vector = getRandomVector(matrix_count_columns, 1);
    }

    std::vector<int> parallel_multiply_on_vector;

    double _time1 = MPI_Wtime();
    parallel_multiply_on_vector = parallelMultiplyOnVector(
                test_matrix, the_test_vector, matrix_count_rows, matrix_count_columns);
    double _time2 = MPI_Wtime();

    if (process_rank == 0) {
        printf("PARRALEL TIME: %.5f\n", _time2-_time1);
        std::vector<int> multiply_on_vector;
        _time1 = MPI_Wtime();
        multiply_on_vector = multiplyOnVector(test_matrix, the_test_vector,
        matrix_count_rows, matrix_count_columns);
        _time2 = MPI_Wtime();
        printf("NOT PARRALEL TIME: %.5f\n", _time2-_time1);
        ASSERT_EQ(multiply_on_vector, parallel_multiply_on_vector);
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
