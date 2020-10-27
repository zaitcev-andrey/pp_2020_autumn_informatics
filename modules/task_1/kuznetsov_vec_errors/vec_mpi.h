#pragma once

#include <vector>

std::vector<int> randV(int size);
void vecNormalize(std::vector<int>& a);
int parallelVector(const std::vector<int>& a, int n);
int countError(const std::vector<int>& a);