// Copyright 2020 Shagov Maksim
#include <mpi.h>
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include "./symbol_count.h"

TEST(Parallel_Symbol_Count_MPI, Test_Empty_String) { // 1
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	const int count_size_string = 0;
	std::string global_string;

	if (rank == 0) {
		global_string = createRandomString(count_size_string);
	}
	ASSERT_ANY_THROW(getParallelSymbolsCount(global_string, count_size_string, global_string[0]));
}

TEST(Parallel_Symbol_Count_MPI, Test_100_Random_Symbols_String) { // 2
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::string global_string;
	const int count_size_string = 100;

	if (rank == 0) {
		global_string = createRandomString(count_size_string);
	}

	int global_sum = getParallelSymbolsCount(global_string, count_size_string, global_string[0]);

	if (rank == 0) {
		int reference_sum = calculateSymbolsCountSequental(global_string, global_string[0]);
		ASSERT_EQ(reference_sum, global_sum);
	}
}

TEST(Parallel_Symbol_Count_MPI, Test_100_Same_Symbols_String) { // 3
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	const int count_size_string = 100;
	std::string global_string(count_size_string, 'a');

	int global_sum = getParallelSymbolsCount(global_string, count_size_string, global_string[0]);

	if (rank == 0) {
		int reference_sum = calculateSymbolsCountSequental(global_string, global_string[0]);
		ASSERT_EQ(reference_sum, global_sum);
	}
}

TEST(Parallel_Symbol_Count_MPI, Test_100_No_Required_Symbols_String) { // 4
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	const int count_size_string = 100;
	std::string global_string(count_size_string, 'a');

	int global_sum = getParallelSymbolsCount(global_string, count_size_string, 'b');

	if (rank == 0) {
		int reference_sum = calculateSymbolsCountSequental(global_string, 'b');
		ASSERT_EQ(reference_sum, global_sum);
	}
}

TEST(Parallel_Symbol_Count_MPI, Test_103_Random_Symbols_String) { // 5
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::string global_string;
	const int count_size_string = 103;

	if (rank == 0) {
		global_string = createRandomString(count_size_string);
	}

	int global_sum = getParallelSymbolsCount(global_string, count_size_string, global_string[0]);

	if (rank == 0) {
		int reference_sum = calculateSymbolsCountSequental(global_string, global_string[0]);
		ASSERT_EQ(reference_sum, global_sum);
	}
}

TEST(Parallel_Symbol_Count_MPI, Test_103_Same_Symbols_String) { // 6
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	const int count_size_string = 103;
	std::string global_string(count_size_string, 'a');

	int global_sum = getParallelSymbolsCount(global_string, count_size_string, global_string[0]);

	if (rank == 0) {
		int reference_sum = calculateSymbolsCountSequental(global_string, global_string[0]);
		ASSERT_EQ(reference_sum, global_sum);
	}
}

TEST(Parallel_Symbol_Count_MPI, Test_1000_Random_Symbols_String) { // 7
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	const int count_size_string = 1000;
	std::string global_string;

	if (rank == 0) {
		global_string = createRandomString(count_size_string);
	}

	int global_sum = getParallelSymbolsCount(global_string, count_size_string, global_string[0]);

	if (rank == 0) {
		int reference_sum = calculateSymbolsCountSequental(global_string, global_string[0]);
		ASSERT_EQ(reference_sum, global_sum);
	}
}

TEST(Parallel_Symbol_Count_MPI, Test_1000_Same_Symbols_String) { // 8
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	const int count_size_string = 1000;
	std::string global_string(count_size_string, 'a');

	int global_sum = getParallelSymbolsCount(global_string, count_size_string, global_string[0]);

	if (rank == 0) {
		int reference_sum = calculateSymbolsCountSequental(global_string, global_string[0]);
		ASSERT_EQ(reference_sum, global_sum);
	}
}


int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	MPI_Init(&argc, &argv);

	::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
	::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

	listeners.Release(listeners.default_result_printer());
	listeners.Release(listeners.default_xml_generator());

	listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
	return RUN_ALL_TESTS();
}
