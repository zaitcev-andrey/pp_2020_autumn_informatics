// Copyright 2020 Panova Olga
#include <mpi.h>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>
#include "../../../modules/task_1/panova_o_max_difference/max_difference.h"
std::vector<int> CreateVector(int size) {
    std::vector<int> v(size);
    // std::random_device rand;
    // std::uniform_int_distribution<int> dis(0, 666);
    // std::generate(v.begin(), v.end(), [&] {return dis(rand);});
    std::mt19937 gen(time(0));
    gen.seed(static_cast<unsigned int>time(0)));
    for (int i = 0; i < size; i++) v[i] = gen() % 100;
    return v;
}
int GetSequentialDifference(std::vector<int> v, int size) {
    int max = abs(v[1] - v[0]);
    int num = 0;
    int* v1 = new int[size];
    for (int i = 1; i < size-1; i++) {
       v1[i] = abs(v[i] - v[i + 1]);
       if (v1[i] > max) {
          max = v1[i];
          num = i;
       }
    }
    return num;
}
int GetParallelDifference(std::vector<int> vec, int vec_size) {
    int p_size, p_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &p_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &p_rank);
    int* v = new int[vec_size];
    int* v1 = new int[vec_size];
    if (p_rank == 0) {
       for (int i = 0; i < vec_size; i++) v[i] = vec[i];
    }
    MPI_Bcast(v, vec_size, MPI_INT, 0, MPI_COMM_WORLD);  //
    struct {
       int value;
       int num;
    }m, max;
    m.value = abs(v[1] - v[0]);
    m.num = 0;
    for (int i = p_rank; i < vec_size-1; i += p_size) {
       v1[i] = abs(v[i] - v[i + 1]);
       if (v1[i] > m.value) {
          m.value = v1[i];
          m.num = i;
       }
    }
    MPI_Reduce(&m, &max, 1, MPI_2INT, MPI_MAXLOC, 0, MPI_COMM_WORLD);  //
    if (p_rank == 0) {
       std::cout << "Max difference between " << v[max.num] << " and " << v[max.num + 1] << std::endl;
       std::cout << "This is the " << max.num << " and " << max.num + 1 << " elements of vector" << std::endl;
    }
    return max.num;
}

