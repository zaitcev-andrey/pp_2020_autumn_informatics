#include <mpi.h>
#include <vector>
#include <random>
#include <ctime>
#include <numeric>
#include "../../../modules/task_1/kulandin_d_matrix_sum/matrix_sum.h"

std::vector<int> randomVector(int sz){
	std::vector<int> ans(sz);
	for(int i = 0;i < sz;++i) ans[i] = (rand() << 15) + rand();
	return ans;
}

long long getParallelSum(const std::vector<int> &a, int n){
	int rank, size;
	long long globalSum = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);		
	const int delta = n / size;
	if (rank == 0){
		for(int j = 1;j < size;++j){
			MPI_Send(&a[0] + j * delta, delta, MPI_INT, j, 0, MPI_COMM_WORLD);
		}
	}
	std::vector<int> local(delta, 0);
	if (rank == 0){
		local = std::vector<int>(a.begin(), a.begin() + delta);		
	} else {
		MPI_Status status;
		MPI_Recv(&local[0], delta, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
	}
	long long localSum = getSequentialSum(local);
	MPI_Reduce(&localSum, &globalSum, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	return globalSum;
}

long long getSequentialSum(const std::vector<int> &vec){
	return std::accumulate(vec.begin(), vec.end(), 0ll);
}


