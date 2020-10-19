#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./sum_elem_row.h"

TEST(Parallel_Operations_MPI, Test_Parallel_Sum) {
	int size_vector = 100;
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::vector<int> global_vec(size_vector);
	int size_row = 25;

	if (rank == 0) {
		global_vec = createRandomMatrix(size_vector);
	}

	std::vector<int> parallel_sum = getParallelOperations(global_vec, size_row);

	if (rank == 0) {
		std::vector<int> sequential_sum = getSequentialOperations(global_vec, size_row);
		ASSERT_EQ(sequential_sum, parallel_sum);
	}
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	MPI_Init(&argc, &argv);

	::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
	::testing::TestEventListeners& listeners =
		::testing::UnitTest::GetInstance()->listeners();

	listeners.Release(listeners.default_result_printer());
	listeners.Release(listeners.default_xml_generator());

	listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
	return RUN_ALL_TESTS();
}