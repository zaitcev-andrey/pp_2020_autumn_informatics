#include <mpi.h>
#include <random>
#include <ctime>
#include <algorithm>
#include "./sents_mpi.h"

std::vector<char> getRandomLine(int size) {
    std::vector<char> sentence(size);
    for (int  i = 0; i < size; i++) {
		int symbol = rand()%255;
        sentence[i] = (char)symbol;
	}
    return sentence;
}

int getSequentialOperations(std::vector<char> sentence) {
    const int  size = sentence.size();
    int ans = 0;
    for (int i = 0; i < size; i++) {
        if (sentence[i] == '!' || sentence[i] == '?' || sentence[i] == '.') ans++;
    }
    return ans;
}

int getParallelOperations(std::vector<char> global_sentence, int count_size_sentence) {
    int size, rank, global_sum_sentences = 0;;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int delta = count_size_sentence / size;
    if (rank == 0) {
        for (int process = 1; process < size; process++) {
            MPI_Send(&global_sentence[0] + process * delta, delta, MPI_CHAR, process, 0, MPI_COMM_WORLD);
        }
    }

    std::vector<char> local_sentence(delta);
    if (rank == 0) {
        local_sentence = std::vector<char>(global_sentence.begin(), global_sentence.begin() + delta);
    } 
	else {
        MPI_Status status;
        MPI_Recv(&local_sentence[0], delta, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
    }
    int local_sum_sentences = getSequentialOperations(local_sentence);
    MPI_Reduce(&local_sum_sentences, &global_sum_sentences, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    return global_sum_sentences;
}
