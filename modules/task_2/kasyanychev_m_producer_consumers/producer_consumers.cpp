// Copyright 2020 Kasyanychev Mikhail
#include <mpi.h>
#include <time.h>
#include <random>
#include "../../../modules/task_2/kasyanychev_m_producer_consumers/producer_consumers.h"

int* generateNum(int size) {
    int* res = new int[size];
    for (int i = 0; i < size; i++) {
        res[i] = i;
    }
    return res;
}

void sqrNum(int* nums, double* res, int size) {
    for (int i = 0; i < size; i++) {
        res[i] = sqrt(nums[i]);
    }
}

void producerConsumers(int* nums, double* res, int sizeArr) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0 && size < 2) {
        sqrNum(nums, res, sizeArr);
        return;
    }

    if (rank == 0 && size >= 2) {
        for (int i = 1; i < sizeArr + 1; ++i) {
            MPI_Status status;
            double tmp = 0;
            MPI_Recv(&tmp, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            if (status.MPI_TAG > 0) {
                res[status.MPI_TAG - 1] = tmp;
            }

            MPI_Send(&(nums[i - 1]), 1, MPI_INT, status.MPI_SOURCE, i, MPI_COMM_WORLD);
        }

        for (int i = 0; i < size - 1; i++) {
            MPI_Status status;
            double tmp = 0;
            MPI_Recv(&tmp, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            if (status.MPI_TAG > 0) {
                res[status.MPI_TAG - 1] = tmp;
            }

            MPI_Send(&i, 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
        }
    } else {
        double tmp = 0;
        MPI_Send(&tmp, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        bool flag = true;

        do {
            int num = 0;
            MPI_Status status;
            MPI_Recv(&num, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            if (status.MPI_TAG == 0) {
                flag = false;
            } else {
                tmp = sqrt(num);
                MPI_Send(&tmp, 1, MPI_DOUBLE, 0, status.MPI_TAG, MPI_COMM_WORLD);
            }
        } while (flag);
    }

    MPI_Barrier(MPI_COMM_WORLD);
}
