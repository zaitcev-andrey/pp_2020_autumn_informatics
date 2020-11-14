// Copyright 2020 Shagov Maksim
#ifndef MODULES_TASK_2_SHAGOV_M_ODD_EVEN_SORT_ODD_EVEN_SORT_H_
#define MODULES_TASK_2_SHAGOV_M_ODD_EVEN_SORT_ODD_EVEN_SORT_H_
#include <vector>
#include <algorithm>

std::vector<int> createRandomVector(int  sz);
void blockMergeArrays(std::vector<int> &arr1, std::vector<int> &arr2);
void oddEvenParallelSort(std::vector<int> &arr);
#endif  // MODULES_TASK_2_SHAGOV_M_ODD_EVEN_SORT_ODD_EVEN_SORT_H_
