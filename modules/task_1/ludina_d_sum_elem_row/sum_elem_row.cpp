#include "../../../modules/task_1/ludina_d_sum_elem_row/sum_elem_row.h"
#include <random>
#include <ctime>
#include <mpi.h>
#include <vector>
#include <iostream>


std::vector<int> createRandomMatrix(int m_size) {
	std::mt19937 gen;
	gen.seed(static_cast<unsigned int>(time(0)));
	std::vector<int> vec(m_size);
	for (int i = 0; i < m_size; i++) {
		vec[i] = gen() % 100;
	}
	return vec;
}

std::vector<int> getSequentialOperations(std::vector<int> vec, int size_row) {
	const int size = vec.size();
	std::vector<int> sum_elem(size / size_row);
	for (int i = 0; i < size_row; i++) {
		for (int j = 0; j < size / size_row; j++) {
			sum_elem[j] += vec[j * size_row + i];
		}
	}
	return sum_elem;
}

std::vector<int> getParallelOperations(std::vector<int> global_vec, int size_row) {
	int size, rank;
	const int vec_size = global_vec.size();
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	const int delta = vec_size / size;
	const int rest = vec_size % size;

	if (rank == 0) {
		for (int proc = 1; proc < size; proc++) {
			if (proc <= rest) {
				MPI_Send(&global_vec[0] + proc * delta + proc - 1,
					delta + 1, MPI_INT, proc, 0, MPI_COMM_WORLD);
			}
			else {
				MPI_Send(&global_vec[0] + proc * delta + rest,
					delta, MPI_INT, proc, 0, MPI_COMM_WORLD);
			}
		}
	}
	std::vector<int> local_vec(delta);

	if (rank == 0) {
		local_vec = std::vector<int>(global_vec.begin(), global_vec.begin() + delta);
	}
	else {
		MPI_Status status;
		if (rank <= rest) {
			local_vec.resize(delta + 1);
			MPI_Recv(&local_vec[0], delta + 1, MPI_INT,
				0, 0, MPI_COMM_WORLD, &status);
		}
		else {
			MPI_Recv(&local_vec[0], delta, MPI_INT,
				0, 0, MPI_COMM_WORLD, &status);
		}
	}
	std::vector<int> global_sum;
	std::vector<int> local_sum = getSequentialOperations(local_vec, size_row);
	MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	return global_sum;
}