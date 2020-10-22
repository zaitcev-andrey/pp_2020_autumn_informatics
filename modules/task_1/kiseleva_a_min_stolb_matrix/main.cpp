#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "./min_stolb.h"
#include <mpi.h>
#include <iostream>
using namespace std;

TEST (Parallel_Operations_MPI, TEST_3x3)
{
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int str = 3;
	int stlb = 3;
	int size = str * stlb;
	vector<vector<int>> matrix = { {1,2,3},{0,0,0},{5,6,9} };
	vector<int> RRes = { 0,0,0 };
	vector<int> linm = VVconvertV(matrix,3,3);
	vector<int> res(3);
	res= Min(linm,3,3);
	if (rank == 0)
	{
		for (int i = 0; i < columns; ++i)
			EXPECT_EQ(RRes[i],res[i]);
	}
}

TEST (Parallel_Operations_MPI, TEST_2x3)
{
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int str = 2;
	int stlb = 3;
	int size = str * stlb;
	vector<vector<int>> matrix = { {0,5,9},{2,3,9} };
	vector<int> RRes = { 0,3,9};
	vector<int> linm = VVconvertV(matrix, 2, 3);
	vector<int> res(3);
	res = Min(linm,2,3);
	if (rank == 0)
	{
		for (int i = 0; i < columns; ++i)
			EXPECT_EQ(RRes[i], res[i]);
	}
}


TEST (Parallel_Operations_MPI, TEST_OTR_EL)
{
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int str = 2;
	int stlb = 2;
	int size = str * stlb;
	vector<vector<int>> matrix = { {-1,-9},{0,-50} };
	vector<int> RRes = { -1,-50};
	vector<int> linm = VVconvertV(matrix, 2, 2);
	vector<int> res(2);
	res = Min(linm,2,2);
	if (rank == 0)
	{
		for (int i = 0; i < columns; ++i)
			EXPECT_EQ(RRes[i], res[i]);
	}
}

TEST(Parallel_Operations_MPI, TEST_RANDOM)
{
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int str = 3;
	int stlb = 3;
	int size = str * stlb;
	vector<vector<int>> matrix = { {0,0,0},{0,0,0},{0,0,0} };
	vector<int> RRes = { 0,0,0 };
	vector<int> linm = VVconvertV(matrix, 3, 3);
	vector<int> res(3);
	res = Min(linm, 3, 3);
	if (rank == 0)
	{
		for (int i = 0; i < columns; ++i)
			EXPECT_EQ(RRes[i], res[i]);
	}
}

TEST(Parallel_Operations_MPI, TEST_RANDOM_NOT_SQUARE)
{
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int str = 3;
	int stlb = 2;
	int size = str * stlb;
	vector<vector<int>> matrix(9);
	matrix = RandomMatrix(3, 2);
	vector<int> linm = VVconvertV(matrix, 3, 2);
	vector<int> res = Min(linm, 3, 2);

}









int main(int argc, char** argv) 
{
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

