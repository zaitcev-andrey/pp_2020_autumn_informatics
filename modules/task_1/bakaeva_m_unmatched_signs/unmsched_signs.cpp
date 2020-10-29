//Copyright 2020 Bakaeva Maria
#include <mpi.h>
#include <ctime>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <random>
#include <ctime>
#include <stdexcept>
#include "unmached_signs.h"

char* generateString(int length) {
    std::mt19937 gen;
    gen.seed((unsigned)time(0) + clock());
    char* str = new char[length + 1];
    const char alpNum[] = "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < length; i++) {
        str[i] = alpNum[gen() % (sizeof(alpNum) - 1)];
    }

    str[length] = '\0';
    return str;
};

int getSequentialUnmachedSignsCount(const char* str1, const char* str2) {
    double t1 = 0, t2 = 0;
    int diff = 0;
    t1 = MPI_Wtime();
    for (int i = 0; i < strlen(str1); i++) {
        if (str1[i] != str2[i]) {
            diff++;
        }
    }

    t2 = MPI_Wtime();

    std::cout << "Linear time = " << t2 - t1 << std::endl;

    return diff;
}

int getParallelUnmachedSignsCount(const char* str1_global, const char* str2_global) {
    int size, rank;
    
    //Число задействованных процессов
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    //Получение номера текущего процесса в рамках коммуникатора
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int local_diff = 0, global_diff = 0;
    double t1 = 0, t2 = 0;
    int length = (int)strlen(str1_global);
    //Длина промежутка для каждого процесса
    const int delta = (length - 1) / size;
    //Длина остатка от всей строки
    const int remainder = (length - 1) % size;

    t1 = MPI_Wtime();
    if (rank == 0) {
            for (int process = 1; process < size; process++) {
                MPI_Send(&str1_global[0] + process * delta + remainder, delta,
                    MPI_CHAR, process, 0, MPI_COMM_WORLD);
                MPI_Send(&str2_global[0] + process * delta + remainder, delta,
                    MPI_CHAR, process, 1, MPI_COMM_WORLD);
            }
    }

    if (rank == 0) {
            char* str1_local = new char[delta + remainder + 1];
            char* str2_local = new char[delta + remainder + 1];
            for (int i = 0; i < (delta + remainder); i++) {
                str1_local[i] = str1_global[i];
                str2_local[i] = str2_global[i];
            }
            
            str1_local[delta + remainder] = '\0';
            str2_local[delta + remainder] = '\0';

            local_diff = getSequentialUnmachedSignsCount(str1_local, str2_local);

            delete[] str1_local;
            delete[] str2_local;

    } else {
        char* str1_local = new char[delta + 1];
        char* str2_local = new char[delta + 1];
        MPI_Status status;
        MPI_Recv(&str1_local[0], delta, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&str2_local[0], delta, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
        
        str1_local[delta + remainder] = '\0';
        str2_local[delta + remainder] = '\0';
        
        local_diff = getSequentialUnmachedSignsCount(str1_local, str2_local);

        delete[] str1_local;
        delete[] str2_local;
    }

    MPI_Reduce(&local_diff, &global_diff, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    t2 = MPI_Wtime();

    std::cout << "MPI time = " << t2 - t1 << std::endl;

    return global_diff;
}
