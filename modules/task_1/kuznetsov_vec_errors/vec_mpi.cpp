#include <mpi.h>
#include <vector>
#include <ctime>
#include <random>
#include "../../../modules/task_1/kuznetsov_vec_errors/vec_mpi.h"

std::vector<int> randV(int size)
{
	std::mt19937 rand_vec;
	std::vector<int> tmp(size);
	rand_vec.seed(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < tmp.size(); i++)
		tmp[i] = rand_vec();
	return tmp;
}

void vecNormalize(std::vector<int>& a)
{
	for (int i = 0; i < a.size() - 1; i++)
	{
		for (int j = 0; j < a.size() - i - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				int tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
}

int parallelVector(const std::vector<int>& a)
{
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int res = a.size() / size;
	int remain = a.size() - res * size;
	if (rank == 0)
	{
		for (int i = 1; i < size; i++)
		{
			if (rank != size - 1)
				MPI_Send(&a + i * res + remain - 1, res, MPI_INT, i, 0, MPI_COMM_WORLD);
			else
				MPI_Send(&a + i * res + remain - 1, res + 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
	}
	std::vector<int> tmp;
	if (rank == 0)
	{
		tmp.resize(res + remain);
		for (int i = 0; i < res + remain; i++)
			tmp[i] = a[i];
	}
	else if (rank != size - 1)
	{
		tmp.resize(res);
		MPI_Status status;
		MPI_Recv(&tmp, res, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
	}
	else
	{
		tmp.resize(res + 1);
		MPI_Status status;
		MPI_Recv(&tmp, res + 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
	}
	int count_sum = countError(tmp);
	int result = 0;
	MPI_Reduce(&count_sum, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	return result;
}

int countError(const std::vector<int>& a)
{
	int count = 0;
	for (int i = 0; i < a.size() - 1; i++)
	{
		if (a[i] > a[i + 1])
			count++;
	}
	return count;
}