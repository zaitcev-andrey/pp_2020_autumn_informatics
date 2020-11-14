// Copyright 2020 Shagov Maksim
#include <mpi.h>
#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>
#include "../../../modules/task_2/shagov_m_odd_even_sort/odd_even_sort.h"

std::vector<int> createRandomVector(int  sz) {
    std::vector<int> result(sz);
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < sz; i++ ) {
        result[i] =  rand_r() % 100;
    }
    return result;
}

void blockMergeArrays(std::vector<int> &arr1, std::vector<int> &arr2) {
    std::vector<int> result(arr1.size() + arr2.size());
    std::copy(arr1.begin(), arr1.end(), result.begin());
    std::copy_backward(arr2.begin(), arr2.end(), result.end());
    std::sort(result.begin(), result.end());
    arr1 = std::vector<int>(result.begin(), result.begin() + arr1.size());
    arr2 = std::vector<int>(result.begin() + arr1.size(), result.end());
}

void oddEvenParallelSort(std::vector<int> &arr) {
    double startT = 0;
    int rank, procCount;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &procCount);
    if (rank == 0) {
        startT = MPI_Wtime();
    }
    MPI_Status status;
    int elements_count = arr.size();
    int elements_part_count = elements_count / procCount;
    int remainder = elements_count % procCount;
    int *revcount = new int[procCount];
    int *displs = new int[procCount];
    revcount[0] = elements_part_count + remainder;
    displs[0] = 0;
    std::vector<int> part_vector(rank == 0 ? elements_part_count + remainder : elements_part_count);
    if (procCount > elements_count) {
        part_vector = arr;
    } else {
        for (int i = 1; i < procCount; i++) {
            revcount[i] = elements_part_count;
            displs[i] = elements_part_count * i + remainder;
        }
        MPI_Scatterv(&arr[0], revcount, displs, MPI_INT, &part_vector[0], revcount[rank], MPI_INT, 0, MPI_COMM_WORLD);
    }
    std::sort(part_vector.begin(), part_vector.end());
    int m = 0;
    std::vector<int> sub;
    if (procCount <= elements_count) {
    for (int i = 0; i < procCount; i++) {
        if (i % 2 == 1) {
            if (rank % 2 == 1) {
                if (rank < procCount - 1) {
                    elements_part_count = part_vector.size();
                    MPI_Send(&elements_part_count, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
                    MPI_Send(&part_vector[0], elements_part_count, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
                    MPI_Recv(&m, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &status);
                    sub.resize(m);
                    MPI_Recv(&sub[0], m, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &status);
                    blockMergeArrays(part_vector, sub);
            }
            } else {
                if (rank > 0) {
                    MPI_Send(&elements_part_count, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
                    MPI_Send(&part_vector[0], elements_part_count, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
                    MPI_Recv(&m, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
                    sub.resize(m);
                    MPI_Recv(&sub[0], m, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
                    blockMergeArrays(sub, part_vector);
                }
            }
        } else {
            if (rank % 2 == 0) {
                if (rank < procCount - 1) {
                    elements_part_count = part_vector.size();
                    MPI_Send(&elements_part_count, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
                    MPI_Send(&part_vector[0], elements_part_count, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
                    MPI_Recv(&m, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &status);
                    sub.resize(m);
                    MPI_Recv(&sub[0], m, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &status);
                    blockMergeArrays(part_vector, sub);
                }
            } else {
                if (rank > 0) {
                    MPI_Send(&elements_part_count, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
                    MPI_Send(&part_vector[0], elements_part_count, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
                    MPI_Recv(&m, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);;
                    sub.resize(m);
                    MPI_Recv(&sub[0], m, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
                    blockMergeArrays(sub, part_vector);
            }
        }
    }
    }
    MPI_Gatherv(&part_vector[0], revcount[rank], MPI_INT,
    &arr[0], revcount, displs, MPI_INT, 0, MPI_COMM_WORLD);
} else {
    arr = part_vector;
}
    if (rank == 0) {
        double endT = MPI_Wtime();
        std::cout << "MPI time: " << endT - startT << std::endl;
    }
}