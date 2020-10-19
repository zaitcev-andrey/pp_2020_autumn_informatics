#include <mpi.h>
#include <vector>
#include <ctime>
#include <random>
#include "../../../modules/task_1/kuznetsov_disordering_of_neighboring_elements/vec_mpi.h"

std::vector<int> randV(int size)
{
	std::mt19937 rand;
	std::vector<int> tmp;
	rand.seed(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < size; i++)
		tmp[i] = rand();
	return tmp;
}

std::vector<int> vecNormalize(const std::vector<int>& a)
{
	std::vector<int> tmp_vec;
	tmp_vec = a;
	for (int i = 0; i < a.size() - 1; i++)
	{
		for (int j = 0; j < a.size() - i - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				int tmp = tmp_vec[j];
				tmp_vec[j] = tmp_vec[j + 1];
				tmp_vec[j + 1] = tmp;
			}
		}
	}
	return tmp_vec;
}

int countErrors(const std::vector<int>& a, int n)
{
	int count = 0;
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	return count;
}