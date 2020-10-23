// Copyright 2020 Ludina Daria
#include "../../../modules/task_1/ludina_d_sum_elem_row/sum_elem_row.h"
#include <random>
#include <ctime>
#include <mpi.h>
#include <vector>

std::vector<int> createRandomMatrix(int rows, int cols) {
	std::mt19937 gen;
	gen.seed(static_cast<unsigned int>(time(0)));
	int m_size = rows * cols;
	std::vector<int> vec(m_size);
	for (int i = 0; i < m_size; i++) {
		vec[i] = gen() % 100;
	}
	return vec;
}

std::vector<int> getSequentialOperations(std::vector<int> vec, int rows, int cols) {
	if (rows * cols == 0)
		throw "Matrix size is incorrect.";
	std::vector<int> sum_elem(rows);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			sum_elem[i] += vec[i * cols + j];
		}
	}
	return sum_elem;
}

std::vector<int> getParallelOperations(std::vector<int> global_vec, int rows, int cols) {
    int size, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	const int delta = rows / size;
	const int rest = rows - delta * size;
	if (rank == 0) {
		for (int proc = 1; proc < size; proc++) {
			MPI_Send(&global_vec[0] + rest * cols + proc * delta * cols, delta * cols, MPI_INT, proc, 0, MPI_COMM_WORLD);
		}
	}
	std::vector<int> local_vec(delta * cols);
	if (rank == 0) {
		local_vec.resize((delta + rest) * cols);
		local_vec = std::vector<int>(global_vec.begin(), global_vec.begin() + (delta + rest) * cols);
	}else {
		MPI_Status status;
		MPI_Recv(&local_vec[0], delta * cols, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
	}
	int local_rows = delta;
	if (rank == 0)
		local_rows += rest;
	std::vector<int> global_sum(rows);
	std::vector<int> local_sum(local_rows);
	if (local_rows > 0)
		local_sum = getSequentialOperations(local_vec, local_rows, cols);
	if (rank == 0) {
		for (int i = 0; i < delta + rest; i++)
			global_sum[i] = local_sum[i];
		for (int proc = 1; proc < size; proc++) {
			MPI_Status status;
			MPI_Recv(&global_sum[0] + rest + delta * proc, delta, MPI_INT, proc, 0, MPI_COMM_WORLD, &status);
		}
	}else {
		MPI_Send(&local_sum[0], delta, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	return global_sum;
}