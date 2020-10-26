// Copyright 2020 Panova Olga
#include <iostream>
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "max_difference.h"

using namespace std;

TEST(Parallel_Operations, Test_Vecint5) {
	vector<int>vec;
	const int vec_size = 5;
	int p_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &p_rank);
	if (p_rank == 0) vec = CreateVector(vec_size);
	int maxnum = GetParallelDifference(vec, vec_size);
	if (p_rank == 0) {
		int num = GetSequentialDifference(vec, vec_size);
		ASSERT_EQ(num, maxnum);
	}
}

TEST(Parallel_Operations, Test_Vecint10) {
	vector<int>vec1;
	const int vec_size = 10;
	int p_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &p_rank);
	if (p_rank == 0) vec1 = CreateVector(vec_size);
	int maxnum = GetParallelDifference(vec1, vec_size);
	if (p_rank == 0) {
		int num = GetSequentialDifference(vec1, vec_size);
		ASSERT_EQ(num, maxnum);
	}
}
TEST(Parallel_Operations, Test_Vecint100) {
	vector<int>vec2;
	const int vec_size = 100;
	int p_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &p_rank);
	if (p_rank == 0) vec2 = CreateVector(vec_size);
	int maxnum = GetParallelDifference(vec2, vec_size);
	if (p_rank == 0) {
		int num = GetSequentialDifference(vec2, vec_size);
		ASSERT_EQ(num, maxnum);
	}
}
TEST(Parallel_Operations, Test_Vecint1000) {
	vector<int>vec3;
	const int vec_size = 1000;
	int p_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &p_rank);
	if (p_rank == 0) vec3 = CreateVector(vec_size);
	int maxnum = GetParallelDifference(vec3, vec_size);
	if (p_rank == 0) {
		int num = GetSequentialDifference(vec3, vec_size);
		ASSERT_EQ(num, maxnum);
	}
}

TEST(Parallel_Operations, Test_Vecint5000) {
	vector<int>vec4;
	const int vec_size = 5000;
	int p_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &p_rank);
	if (p_rank == 0) vec4 = CreateVector(vec_size);
	int maxnum = GetParallelDifference(vec4, vec_size);
	if (p_rank == 0) {
		int num = GetSequentialDifference(vec4, vec_size);
		ASSERT_EQ(num, maxnum);
	}
}
int main(int argc, char** argv)
{
	int res = 0;
	::testing::InitGoogleTest(&argc, argv);
	MPI_Init(&argc, &argv);

	::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
	::testing::TestEventListeners& lst = ::testing::UnitTest::GetInstance()->listeners();
	lst.Release(lst.default_result_printer());
	lst.Release(lst.default_xml_generator());
	lst.Append(new GTestMPIListener::MPIMinimalistPrinter);
	res = RUN_ALL_TESTS();

	//MPI_Finalize();
	return res;
}

