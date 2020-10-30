// Copyright 2020 Bessolitsyn Sergey
#include <mpi.h>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <cstring>
#include "../../../modules/task_1/bessolitsyn_s_count_sent/count_sent.h"


std::vector<char> getRandomString(int n) {
    const std::string char_arr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz .!?";
    std::vector<char> vec(n);
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < n; ++i) {
        vec[i] = gen() % char_arr.size();
    }
    return vec;
}

int getSequentialOperations(std::vector<char> vec, int n) {
    int counter = 0;
    double t_1, t_2;
    t_1 = MPI_Wtime();
    for (int i = 0; i < n; ++i) {
        bool tmp = vec[i] == '.' || vec[i] == '?' || vec[i] == '!';
        for (; tmp && (i + 1) < n && (vec[i + 1] == '.' || vec[i + 1] == '?' || vec[i + 1] == '!'); ++i) {}
        counter += static_cast<int>(tmp);
    }
    t_2 = MPI_Wtime();
    std::cout << "Sequentional time: " << t_2 - t_1 << std::endl;
    return counter;
}

int getParallelOperations(std::vector<char> global_vec, int count_size_vector) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double t_1, t_2;
    if (rank == 0) {
        t_1 = MPI_Wtime();
    }

    const int delta = count_size_vector / size;
    const int rem = count_size_vector % size;
    char* local_string;
    const int n = (rank == 0) ? delta : (delta + static_cast<int>(rank <= rem));
    local_string = new char[n];
    int global_res = 0, local_res = 0;

    if (rank == 0) {
        for (int proc = 1; proc < size; ++proc) {
            if (proc <= rem) {
                MPI_Send(&global_vec[0] + proc * delta + proc - 1,
                    delta + 1, MPI_INT, proc, 0, MPI_COMM_WORLD);
            } else {
                MPI_Send(&global_vec[0] + proc * delta + rem, delta, MPI_INT, proc, 0, MPI_COMM_WORLD);
            }
        }
    }

    if (rank == 0) {
        for (int i = 0; i < delta; ++i) {
            local_string[i] = global_vec[i];
        }
    } else {
        MPI_Status status;
        MPI_Recv(local_string, n, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }
    for (int i = 0; i < n; ++i) {
        bool tmp = (local_string[i] == '.' || local_string[i] == '?' || local_string[i] == '!');
        for (; tmp && (i + 1) < n &&
            (local_string[i + 1] == '.' || local_string[i + 1] == '?' || local_string[i + 1] == '!'); ++i) {}
        local_res += static_cast<int>(tmp);
    }

    MPI_Reduce(&local_res, &global_res, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    delete[] local_string;
    if (rank == 0) {
        t_2 = MPI_Wtime();
        std::cout << "Parallel time: " << t_2 - t_1 << std::endl;
    }
    return global_res;
}


