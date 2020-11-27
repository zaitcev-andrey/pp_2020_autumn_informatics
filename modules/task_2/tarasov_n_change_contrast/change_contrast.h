#pragma once

#include <vector>

std::vector<int> set_random_img(int _width, int _high);
void print_img(std::vector<int> pic, int _high, int _width);
std::vector<int> changeContrast(std::vector<int> &pic, int _width, int _high, int _correction);
std::vector<int> changeContrastParallel(std::vector<int> &pic, int _width, int _high, int _correction);
