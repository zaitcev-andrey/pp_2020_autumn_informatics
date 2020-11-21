// Copyright 2020 Lyutova Tanya
#include <mpi.h>
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include "../../../modules/task_2/lyutova_t_sleeping_barber/sleeping_barber.h"


TEST(doBarber, TEST_ASSSERT1) {
    int vis_size;
    MPI_Comm_size(MPI_COMM_WORLD, &vis_size);
    if (vis_size < 2) {
        ASSERT_ANY_THROW(launch());
    }
}

TEST(doBarber, TEST_ASSSERT2) {
    int vis_size;
    MPI_Comm_size(MPI_COMM_WORLD, &vis_size);
    if (vis_size > 1) {
        ASSERT_NO_THROW(launch);
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    launch();
    MPI_Finalize();
}
