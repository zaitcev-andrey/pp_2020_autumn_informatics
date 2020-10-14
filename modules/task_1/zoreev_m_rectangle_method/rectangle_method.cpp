#include "rectangle_method.h"

double Integralseqential(double (*funсtion)(double),double a, double b, size_t count)
{
    double result = 0, delta = (b - a) / count;
    for (size_t i = 0; i < count; i++)
    {
        result += funсtion(a + delta * i);
    }
    result *= delta;
    return result;
}

double Integralparallel(double (*funсtion)(double), double a, double b, size_t count)
{
    int rank, process_count;
    double delta = (b - a) / count;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    size_t part = count / static_cast<size_t>(process_count);
    double result = 0, local_result = 0;
    if (rank != process_count - 1)
    {
        local_result = Integralseqential(funсtion, a + rank * (part * delta), a + (rank + 1) * (part * delta), part);
    }
    else
    {
        local_result = Integralseqential(funсtion, a + rank * (part * delta), b, count - part * (process_count - 1));
    }
    MPI_Reduce(&local_result, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    return result;
}
