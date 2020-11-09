// Copyright 2020 Volkova Anastasia
#include <mpi.h>
#include <cstring>
#include "../../../modules/task_2/volkova_a_scatter/scatter_mpi.h"

int MY_Scatter(void* sendBuf, int sendCount,
               MPI_Datatype sendType, void* recvBuf,
               int recvCount, MPI_Datatype recvType,
               int ROOT, MPI_Comm COMM) {
    if (sendCount != recvCount)return MPI_ERR_COUNT;
    if (sendCount <= 0) return MPI_ERR_COUNT;
    if (recvCount <= 0) return MPI_ERR_COUNT;
    if (sendBuf == nullptr) return MPI_ERR_BUFFER;
    int size;
    int rank;
    int sizeTypeSend;
    int sizeTypeRecv;
    int tag = 15;

    if (MPI_Comm_size(MPI_COMM_WORLD, &size) != MPI_SUCCESS) {
        MPI_Status stat;
        return stat.MPI_ERROR;
    }
    if (MPI_Comm_rank(MPI_COMM_WORLD, &rank) != MPI_SUCCESS) {
        MPI_Status stat;
        return stat.MPI_ERROR;
    }
    if (MPI_Type_size(sendType, &sizeTypeSend) != MPI_SUCCESS) {
        MPI_Status stat;
        return stat.MPI_ERROR;
    }
    if (MPI_Type_size(recvType, &sizeTypeRecv) != MPI_SUCCESS) {
        MPI_Status stat;
        return stat.MPI_ERROR;
    }

    if (ROOT >= size || ROOT < 0)return MPI_ERR_ROOT;

    if (rank == ROOT) {
        for (int i = 0; i < size; ++i) {
            if (i != ROOT) {
                int qq = i * sendCount * sizeTypeSend;
                MPI_Send(static_cast<char*>(sendBuf) + qq, sendCount, sendType, i, tag, COMM);
            }
        }
        int lolo = sendCount * sizeTypeSend;
        int k = rank * lolo;
        std::memcpy(recvBuf, static_cast<char*>(sendBuf) + k, lolo);
    } else {
        MPI_Status STATUS;
        MPI_Recv(recvBuf, recvCount, recvType, ROOT, tag, COMM, &STATUS);
    }

    return MPI_SUCCESS;
}


