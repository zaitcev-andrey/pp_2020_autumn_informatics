// Copyright 2020 Prokofeva Elizaveta
#ifndef MODULES_TASK_2_PROKOFEVA_E_LINEAR_ARRAY_LINEAR_ARRAY_H_
#define MODULES_TASK_2_PROKOFEVA_E_LINEAR_ARRAY_LINEAR_ARRAY_H_

int* getRandomVector(int size);
MPI_Comm create_comm(MPI_Comm comm);
int* send_recv(int* buf, int count, MPI_Datatype type, int dest, int tag, MPI_Comm comm, int source, int ProcRank);

#endif  // MODULES_TASK_2_PROKOFEVA_E_LINEAR_ARRAY_LINEAR_ARRAY_H_
