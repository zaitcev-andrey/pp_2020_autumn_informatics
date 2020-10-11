#include <mpi.h>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include "../../../modules/test_tasks/test_mpi/ops_mpi.h"


std::vector<char> getRandomLine(int size) {
    std::vector<char> vec(size);
    for (int  i = 0; i < size; i++) {
		int a = rand()%255;
        vec[i] = (char)a; 
		}
    return vec;
}

int getSequentialOperations(std::vector<char> vec) {
    const int  size = vec.size();
    int ans = 0;
    for (int i = 0; i < size; i++) {
        if (vec[i] == '!' || vec[i] == '?' || vec[i] == '.') ans++;
    }
    return ans;
}

int getParallelOperations(std::vector<char> global_vec, int count_size_vector) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int delta = count_size_vector / size;

    if (rank == 0) {
        for (int process = 1; process < size; process++) {
            MPI_Send(&global_vec[0] + process * delta, delta, MPI_CHAR, process, 0, MPI_COMM_WORLD);
        }
    }

    std::vector<char> local_vec(delta);
    if (rank == 0) {
        local_vec = std::vector<char>(global_vec.begin(), global_vec.begin() + delta);
    } 
	else {
        MPI_Status status;
        MPI_Recv(&local_vec[0], delta, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
    }

    int global_sum = 0;
    int local_sum = getSequentialOperations(local_vec);
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    return global_sum;
}
