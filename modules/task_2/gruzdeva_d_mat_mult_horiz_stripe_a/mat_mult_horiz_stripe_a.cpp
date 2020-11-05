// Copyright 2020 Gruzdeva Diana

#include "../../../modules/task_2/gruzdeva_d_mat_mult_horiz_stripe_a/mat_mult_horiz_stripe_a.h"
#include <random>  
#include <ctime>  


int** getRandomMatrix(int width, int height, time_t seed) {
	int** mat;
	mat = new int*[height];
	for (int i = 0; i < height; i++) {
		mat[i] = new int[width];
	}
	std::mt19937 gen;
	gen.seed(static_cast<unsigned int>(seed));
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			// mat[i][j] = gen() % 100;
			mat[i][j] = gen() % 10;
		}
	}
	return mat;
}

int** getSequentialMultiplication(int** matrixA, int** matrixB, int matrixAHeight, int matrixAWidth, int matrixBWidth) {
	int** matrixC;
	matrixC = new int*[matrixBWidth];
	for (int i = 0; i < matrixAHeight; i++) {
		matrixC[i] = new int[matrixBWidth];
	}
	for (int i = 0; i < matrixAHeight; i++) {
		for (int j = 0; j < matrixBWidth; j++) {
			matrixC[i][j] = 0;
			for (int k = 0; k < matrixAWidth; k++) {
				matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}
	return matrixC;
}