// Copyright 2020 Belik Julia
#include <mpi.h>
#include <cmath>
#include <functional>
#include "../../../modules/task_1/belik_j_integration_trapez/IntegrationTrapez.h"

double getSequentialIntegration(const std::function<double(double)>& f, double a, double b, int n) {
    double sum = 0;
    double interval = (b - a) / n;
    for (int i = 0; i < n; i++)
        sum += ((f(a + (i + 1) * interval) + f(a + i * interval)) / 2);
    sum *= interval;
    return sum;
}

double getParallelIntegration(const std::function<double(double)>& f, double a, double b, int n) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (size == 1 || n < size)
        return getSequentialIntegration(f, a, b, n);
    double interval = (b - a) / static_cast<double>(n);
    int count_interv = n / size;
    double local_integral = 0, global_integral = 0;
    double begin_interval = a + static_cast<double>(rank) * interval;
    double end_interval = begin_interval + interval;
    local_integral = getSequentialIntegration(f, begin_interval, end_interval, count_interv);
    MPI_Reduce(&local_integral, &global_integral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    return global_integral;
}
