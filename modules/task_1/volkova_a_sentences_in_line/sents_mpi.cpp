// Copyright 2020 Volkova Anastasia
#include <mpi.h>
#include <random>
#include <ctime>
#include <algorithm>
#include "./sents_mpi.h"

std::vector<char> getRandomLine(int size) {
    std::vector<char> line(size);
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    int symbol;
    for (int i = 0; i < size; i++) {
        symbol = gen() % 255;
        line[i] = static_cast<char>(symbol);
    }
    return line;
}

int getSequentialSumSentences(std::vector<char> line) {
    const int  size = line.size();
    int ans = 0;
    for (int i = 0; i < size; i++) {
        if (line[i] == '!' || line[i] == '?' || line[i] == '.') ans++;
    }
    return ans;
}

int getParallelSumSentences(std::vector<char> global_line, int size_line) {
    int size, rank, global_sum_sentences = 0;;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int delta = size_line / size;
    if (rank == 0) {
        for (int process = 1; process < size; process++) {
            MPI_Send(&global_line[0] + process * delta, delta, MPI_CHAR, process, 0, MPI_COMM_WORLD);
        }
    }

    std::vector<char> local_line(delta);
    if (rank == 0) {
        local_line = std::vector<char>(global_line.begin(), global_line.begin() + delta);
    } else {
        MPI_Status status;
        MPI_Recv(&local_line[0], delta, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
    }
    int local_sum_sentences = getSequentialSumSentences(local_line);
    MPI_Reduce(&local_sum_sentences, &global_sum_sentences, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    return global_sum_sentences;
}
