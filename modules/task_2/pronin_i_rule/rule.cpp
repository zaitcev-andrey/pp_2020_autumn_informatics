// Copyright 2020 Pronin Igor
#include <mpi.h>
#include "../../../modules/task_2/pronin_i_rule/rule.h" 
MPI_Comm createRuleComm(MPI_Comm comunicator, int q)
{
	int ndims = 1;
	int size;
	MPI_Comm_size(comunicator, &size);
	MPI_Comm  RuleComm;
	int* dims = new int[1]{0};
	int* periods = new int[1]{0};
	if (q <= 0 || q > size)
		MPI_Dims_create(size, 1, dims);
	else
		MPI_Dims_create(q, 1, dims);
	MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, 0, &RuleComm);
	delete[] dims;
	delete[] periods;
	return RuleComm;
}