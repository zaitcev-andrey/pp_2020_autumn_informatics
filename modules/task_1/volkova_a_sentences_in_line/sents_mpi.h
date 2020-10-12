// Copyright 2020 Volkova Anastasia
#ifndef MODULES_TASK_1_VOLKOVA_A_SENTENCES_IN_LINE_SENTS_MPI_H_
#define MODULES_TASK_1_VOLKOVA_A_SENTENCES_IN_LINE_SENTS_MPI_H_

#include <vector>

std::vector<char> getRandomLine(int  size);
int getSequentialOperations(std::vector<char> sentence);
int getParallelOperations(std::vector<char> global_vec, int count_size_sentence);

#endif  // MODULES_TASK_1_VOLKOVA_A_SENTENCES_IN_LINE_SENTS_MPI_H_
