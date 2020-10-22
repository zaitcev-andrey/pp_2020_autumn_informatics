// Copyright 2020 Streltsova Yana
#include <mpi.h>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>
#include "../../../modules/task_1/streltsova_y_min_distance/min_distance.h"

std::vector<int> getRandomVector(int size) {
    std::mt19937 gen(time(0));
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<int> vec(size);
    for (int i = 0; i < size; i++) { vec[i] = gen() % 100; }
    return vec;
}

int getSequentialOperations(std::vector<int> vec, int size_vector) {
    double t1, t2;
    t1 = MPI_Wtime();
    int min = abs(vec[1] - vec[0]);
    int idx = 0;
    for (int i = 1; i < size_vector - 1; i++)
        if (abs(vec[i + 1] - vec[i]) < min) {
            min = abs(vec[i + 1] - vec[i]);
            idx = i;
        }
    t2 = MPI_Wtime();
    std::cout.precision(10);
    std::cout << "Seq_time = " << std::fixed << t2 - t1 << std::endl;
    return idx;
}

int getParallelOperations(std::vector<int> global_vec, int size_vector) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double t1, t2;
    int* local_vec = new int[size_vector];
    if (rank == 0) {
        t1 = MPI_Wtime();
        for (int i = 0; i < size_vector; i++)
            local_vec[i] = global_vec[i];
    }
    MPI_Bcast(local_vec, size_vector, MPI_INT, 0, MPI_COMM_WORLD);
    struct {
        int value;
        int idx;
    }local_min, global_min;
    local_min.value = abs(local_vec[1] - local_vec[0]);
    local_min.idx = 0;
    for (int i = rank; i < size_vector - 1; i += size)
        if (abs(local_vec[i + 1] - local_vec[i]) < local_min.value) {
            local_min.value = abs(local_vec[i + 1] - local_vec[i]);
            local_min.idx = i;
        }
    MPI_Reduce(&local_min, &global_min, 1, MPI_2INT, MPI_MINLOC, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        t2 = MPI_Wtime();
        std::cout << "Closest Neighbors: i1 = " << global_min.idx
                  << ", i2 = " << global_min.idx + 1 << std::endl;
        std::cout << "Distance = " << global_min.value << std::endl;
        std::cout.precision(10);
        std::cout << "Par_time = " << std::fixed << t2 - t1 << std::endl;
    }
    return global_min.idx;
}
