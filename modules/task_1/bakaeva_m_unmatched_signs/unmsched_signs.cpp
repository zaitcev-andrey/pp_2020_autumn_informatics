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

    std::cout << "Linear result = " << diff << std::endl;
    std::cout << "Linear time = " << t2 - t1 << std::endl;

    return diff;
}

int getParallelUnmachedSignsCount(const char* str1_global, const char* str2_global) {
    int size, rank;
    int local_diff = 0, global_diff = 0;
    double t1 = 0, t2 = 0;
    int length = (int)strlen(str1_global);
    //Число задействованных процессов
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
     //Получение номера текущего процесса в рамках коммуникатора
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char* str1_local = new char[length + 1];
    char* str2_local = new char[length + 1];

    if (rank == 0) {
        t1 = MPI_Wtime();
        for (int i = 0; i < length + 1; i++) {
            str1_local[i] = str1_global[i];
            str2_local[i] = str2_global[i];
        }
    }

    MPI_Bcast(str1_local, length, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(str2_local, length, MPI_CHAR, 0, MPI_COMM_WORLD);

    for (int i = rank; i <= length + 1; i += size) {
        if (str1_local[i] != str2_local[i])
            local_diff++;
    }

    //Операция приведения, получение результата в главный процессор
    MPI_Reduce(&local_diff, &global_diff, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        t2 = MPI_Wtime();
        std::cout << "MPI result = " << global_diff << std::endl;
        std::cout << "MPI time = " << t2 - t1 << std::endl;
    }

    delete[] str1_local;
    delete[] str2_local;

    return global_diff;
}
