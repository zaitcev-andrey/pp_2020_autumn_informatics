// Copyright 2020 Shirokov Sergey
#ifndef MODULES_TASK_1_SHIROKOV_S_MATRIX_MIN_MIN_ELEM_MATRIX_H_
#define MODULES_TASK_1_SHIROKOV_S_MATRIX_MIN_MIN_ELEM_MATRIX_H_
#include <random>
#include <iostream>
#include <vector>

void matrix_enter(int sizel_f, int sizec_f, int* a[]) {
    std::random_device rd;
    std::mt19937 number(rd());
    for (int i = 0; i < sizel_f; i++) {
        for (int j = 0; j < sizec_f; j++) {
            a[i][j] = static_cast<int>(number() % 100u);
        }
    }
}
void enter_massive(int sizel_f, int* a) {
    for (int i = 0; i < sizel_f; i++) {
        a[i] = 0;
        std::cout << a[i] << " ";
    }
}
void recurv_massive(int sizel_f, int* a) {
    for (int i = 0; i < sizel_f; i++) {
        a[i]++;
        std::cout << a[i] << " ";
    }
}
void matrix_print(int sizel_f, int sizec_f, int* a[]) {
    for (int i = 0; i < sizel_f; i++) {
        for (int j = 0; j < sizec_f; j++) {
            std::cout << a[i][j] << " ";
            if ((a[i][j] / 10) == 0)
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}
void massive_ent(int sizel_f, int sizec_f, int* a[], int a1[]) {
    for (int i = 0; i < sizec_f; i++) {
        a1[i] = a[sizel_f][i];
    }
}
int min_el(int sizec_f, int a[]) {
    int min = 0;
    for (int i = 0; i < sizec_f; i++) {
        if (i == 0)
            min = a[i];
        if (a[i] < min)
            min = a[i];
    }
    return min;
}
int maxElementMatrix(int sizel_f, int sizec_f);

#endif  // MODULES_TASK_1_SHIROKOV_S_MATRIX_MIN_MIN_ELEM_MATRIX_H_
