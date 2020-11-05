// Copyright 2020 Zoreev Mikhail

#include <mpi.h>

#include "../../../lattice_torus.h"

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    MPI_Comm communicator = createLatticeTorus(MPI_COMM_WORLD, 2);
    MPI_Finalize();
}
